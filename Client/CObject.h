#pragma once



class CCollider;
class CAnimator;
class CRigidBody;


class CObject
{
private:
	wstring		m_strName; // 오브젝트의 이름

	Vec2		m_vPos;
	Vec2		m_vScale;

	// Component
	CCollider*	m_pCollider;
	CAnimator*  m_pAnimator;
	CRigidBody* m_pRigidBody;

	bool		m_bAlive; // 오브젝트의 생존

public:
	void SetPos(Vec2 _vPos) { m_vPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetPos() { return m_vPos; }
	Vec2 GetScale() { return m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	const wstring& GetName() { return m_strName; }

	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }

	bool IsDead() { return !m_bAlive; }

	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();

	virtual void OnCollision(CCollider* _pOther) {}			// 충돌 중인 경우 호출되는 함수
	virtual void OnCollisionEnter(CCollider* _pOther) {}	// 이번에 충돌한 경우 호출되는 함수
	virtual void OnCollisionExit(CCollider* _pOther) {}		// 이번에 충돌에서 벗어난 경우
private:
	void SetDead() { m_bAlive = false; }


public:
	virtual void update() = 0;
	virtual void finalUpdate();
	virtual void render(HDC _dc);

	void component_render(HDC _dc);

	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual ~CObject();

	friend class EventMgr;
};

