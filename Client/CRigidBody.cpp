#include "pch.h"
#include "CRigidBody.h"

#include "CObject.h"
#include "TimeMgr.h"


CRigidBody::CRigidBody()
	: m_pOwner(nullptr)
	, m_fMass(0.f)
	, m_fMaxSpeed(0.f)
	, m_fFricCoeff(100.f)
{
}

CRigidBody::~CRigidBody()
{
}

void CRigidBody::finalupdate()
{
	// 힘의 크기
	float fForce = m_vForce.Length();


	if (0.f != fForce)
	{
		// 힘의 방향
		m_vForce.Normalize();

		// 가속도의 크기
		float m_fAccel = fForce / m_fMass;

		// 가속도
		m_vAccel = m_vForce * m_fAccel;

		// 속도
		m_vVeloCity += m_vAccel * fDeltaTime;
	}
		

	// 마찰력에 의한 반대방향으로의 가속도
	if (!m_vVeloCity.IsZero())
	{
		Vec2 vFricDir = m_vVeloCity;
		Vec2 vFriction = -vFricDir.Normalize() * m_fFricCoeff * fDeltaTime;
		if (m_vVeloCity.Length() <= vFriction.Length())
		{
			// 마찰 가속도가 본래 속도보다 더 큰 경우
			m_vVeloCity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVeloCity += vFriction;
		}
		
	}
	// 속도 제한 검사
	if (m_fMaxSpeed < m_vVeloCity.Length())
	{
		m_vVeloCity.Normalize();
		m_vVeloCity *= m_fMaxSpeed;
	}
	// 속도에 따른 이동
	Move();

	// 힘 초기화
	m_vForce = Vec2(0.f, 0.f);
}

void CRigidBody::Move()
{
	if (0.f != m_vVeloCity.Length())
	{
		Vec2 vPos = m_pOwner->GetPos();

		vPos += m_vVeloCity * fDeltaTime;

		m_pOwner->SetPos(vPos);
	}
}
