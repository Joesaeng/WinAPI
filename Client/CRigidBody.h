#pragma once

class CObject;

class CRigidBody
{
private:
	CObject*	m_pOwner;		// RigidBody�� �����ϰ� �ִ� ������Ʈ

	Vec2		m_vForce;		// ���� ũ��, ����
	Vec2		m_vAccel;		// ���ӵ�
	Vec2		m_vVeloCity;	// �ӵ�( ũ�� : �ӷ�, ����)
	float		m_fMaxSpeed;	// �ִ� �ӷ�
	float		m_fMass;		// ����


	float		m_fFricCoeff;	// ���� ��� **Friction Coefficient

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

