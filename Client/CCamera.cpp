#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "ResourceMgr.h"
#include "CTexture.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(1.f)
	, m_fAccTime(0.f)
	, m_fSpeed(0.f)
	, m_pVeilTex(nullptr)
{
}

CCamera::~CCamera()
{

}



void CCamera::update()
{
	if (m_pTargetObj)
	{
		if (m_pTargetObj->IsDead())
		{
			m_pTargetObj = nullptr;
		}
		else
		{
			m_vLookAt = m_pTargetObj->GetPos();
		}

	}
	if(KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDeltaTime;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDeltaTime;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDeltaTime;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDeltaTime;



	// ȭ�� �߾���ǥ�� ī�޶� LookAt ��ǥ���� ���̰� ���
	CalDiff();
}

void CCamera::init()
{
	Vec2 vResoultion = CCore::GetInst()->GetResolution();
	m_pVeilTex = ResourceMgr::GetInst()->CreateTexture(L"CamVeilTex", (UINT)vResoultion.x, (UINT)vResoultion.y);
	// �ؽ��ĸ� ���� �������� ��, �ʱ� RGB ���� (0,0,0)�̴�.
}

void CCamera::render(HDC _dc)
{
	if (m_listCamEffect.empty())
		return;
	
	// �ð� �������� üũ
	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += fDeltaTime;

	

	float fRatio = 0.f; // ����Ʈ ���� ����
	fRatio = effect.fCurTime / effect.fDuration;

	if (fRatio < 0.f)
		fRatio = 0.f;
	if (fRatio > 1.f)
		fRatio = 1.f;

	int iAlpha = 0;

	switch (effect.eEffect)
	{
	case CAM_EFFECT::FADE_OUT:
		iAlpha = (int)(255.f * fRatio);
		break;
	case CAM_EFFECT::FADE_IN:
		iAlpha = (int)(255.f * (1.f - fRatio));
		break;
	default:
		break;
	}

	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = iAlpha;

	AlphaBlend(_dc, 0, 0
		, (int)m_pVeilTex->Width() 
		, (int)m_pVeilTex->Height()
		, m_pVeilTex->GetDC(), 0, 0
		, (int)m_pVeilTex->Width()
		, (int)m_pVeilTex->Height()
		, bf);

	// ���� �ð��� ����Ʈ �����ų �ð��� �Ѿ ���
	if (effect.fDuration < effect.fCurTime)
	{
		// ����Ʈ�� �����Ѵ�
		m_listCamEffect.pop_front();
		return;
	}
}

void CCamera::CalDiff()
{
	// ���� LookAt �� ���� Look �� ���̰��� �����ؼ� ������ LookAt �� ���Ѵ�.

	m_fAccTime += fDeltaTime;

	if (m_fTime <= m_fAccTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		if (m_vLookAt != m_vPrevLookAt)
		{
			Vec2 vLookDir = (m_vLookAt - m_vPrevLookAt).Normalize();
			m_vCurLookAt = m_vPrevLookAt + vLookDir * m_fSpeed * fDeltaTime;
		}
		else
		{
			m_vCurLookAt = m_vPrevLookAt;
		}
	}
	

	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2;

	m_vDiff = m_vCurLookAt - vCenter;
	m_vPrevLookAt = m_vCurLookAt;
}
