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
	// ���� ũ��
	float fForce = m_vForce.Length();


	if (0.f != fForce)
	{
		// ���� ����
		m_vForce.Normalize();

		// ���ӵ��� ũ��
		float m_fAccel = fForce / m_fMass;

		// ���ӵ�
		m_vAccel = m_vForce * m_fAccel;

		// �ӵ�
		m_vVeloCity += m_vAccel * fDeltaTime;
	}
		

	// �����¿� ���� �ݴ���������� ���ӵ�
	if (!m_vVeloCity.IsZero())
	{
		Vec2 vFricDir = m_vVeloCity;
		Vec2 vFriction = -vFricDir.Normalize() * m_fFricCoeff * fDeltaTime;
		if (m_vVeloCity.Length() <= vFriction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ���
			m_vVeloCity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVeloCity += vFriction;
		}
		
	}
	// �ӵ� ���� �˻�
	if (m_fMaxSpeed < m_vVeloCity.Length())
	{
		m_vVeloCity.Normalize();
		m_vVeloCity *= m_fMaxSpeed;
	}
	// �ӵ��� ���� �̵�
	Move();

	// �� �ʱ�ȭ
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
