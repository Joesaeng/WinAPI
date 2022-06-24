#include "pch.h"
#include "CCamera.h"

#include "CObject.h"
#include "CCore.h"

#include "TimeMgr.h"
#include "KeyMgr.h"

CCamera::CCamera()
	: m_pTargetObj(nullptr)
	, m_fTime(1.f)
	, m_fAccTime(0.f)
	, m_fSpeed(0.f)
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
		if (Vec2(0.f, 0.f) != (m_vLookAt - m_vPrevLookAt))
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
