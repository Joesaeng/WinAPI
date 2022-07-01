#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;		// RigidBody�� �����ϰ� �ִ� ������Ʈ

	Vec2		m_vForce;		// ���� ũ��, ����
	Vec2		m_vAccel;		// ���ӵ�
	Vec2		m_vVeloCity;	// �ӵ�( ũ�� : �ӷ�, ����)
	float		m_fMass;		// ����

	// F = M * A
	// V += A * DeltaTime


public:
	void finalupdate();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

