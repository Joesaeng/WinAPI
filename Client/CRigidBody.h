#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;		// RigidBody를 소유하고 있는 오브젝트

	Vec2		m_vForce;		// 힘의 크기, 방향
	Vec2		m_vAccel;		// 가속도
	Vec2		m_vVeloCity;	// 속도( 크기 : 속력, 방향)
	float		m_fMaxSpeed;	// 최대 속력
	float		m_fMass;		// 질량


	float		m_fFricCoeff;	// 마찰 계수 **Friction Coefficient

	// F = M * A
	// V += A * DeltaTime



public:
	void finalupdate();

public:
	void AddForce(Vec2 _vf){m_vForce += _vf;}
	void SetMass(float _fMass) { m_fMass = _fMass; }
	float GetMass() { return m_fMass; }

	void SetVelocity(Vec2 _vVelocity) { m_vVeloCity = _vVelocity; }
	void AddVelocity(Vec2 _vVelocity) { m_vVeloCity += _vVelocity; }
	void SetMaxSpeed(float _fSpeed) { m_fMaxSpeed = _fSpeed; }
	Vec2 GetVelocity() { return m_vVeloCity; }
	float GetSpeed() { return m_vVeloCity.Length(); }

private:
	void Move();

public:
	CRigidBody();
	~CRigidBody();

	friend class CObject;
};

