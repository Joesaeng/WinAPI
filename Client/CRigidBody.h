#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;		// RigidBody를 소유하고 있는 오브젝트

	Vec2		m_vForce;		// 힘의 크기, 방향
	Vec2		m_vAccel;		// 가속도
	Vec2		m_vVeloCity;	// 속도( 크기 : 속력, 방향)
	float		m_fMass;		// 질량

	// F = M * A
	// V += A * DeltaTime


public:
	void finalupdate();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

