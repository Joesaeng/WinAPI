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



	// 화면 중앙좌표와 카메라 LookAt 좌표간의 차이값 계산
	CalDiff();
}

void CCamera::init()
{
	Vec2 vResoultion = CCore::GetInst()->GetResolution();
	m_pVeilTex = ResourceMgr::GetInst()->CreateTexture(L"CamVeilTex", (UINT)vResoultion.x, (UINT)vResoultion.y);
	// 텍스쳐를 새로 생성했을 때, 초기 RGB 값은 (0,0,0)이다.
}

void CCamera::render(HDC _dc)
{
	if (m_listCamEffect.empty())
		return;
	
	// 시간 누적값을 체크
	tCamEffect& effect = m_listCamEffect.front();
	effect.fCurTime += fDeltaTime;

	

	float fRatio = 0.f; // 이펙트 진행 비율
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

	// 진행 시간이 이펙트 진행시킬 시간을 넘어선 경우
	if (effect.fDuration < effect.fCurTime)
	{
		// 이펙트를 종료한다
		m_listCamEffect.pop_front();
		return;
	}
}

void CCamera::CalDiff()
{
	// 이전 LookAt 과 현재 Look 의 차이값을 보정해서 현재의 LookAt 을 구한다.

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
