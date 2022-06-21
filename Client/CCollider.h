#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject*	m_pOwner;			// Collider를 소유하고 있는 오브젝트
	Vec2		m_vOffsetPos;		// 오브젝트로부터 상대적인 위치
	Vec2		m_vFinalPos;		// finalupdate 에서 매 프레임마다 계산
	Vec2		m_vColliderScale;	// 충돌체 크기

	UINT		m_iID;				// 충돌체 고유한 ID 값
	UINT		m_iCol;

public:
	void SetOffsetPos(Vec2 _vPos) {m_vOffsetPos = _vPos;}
	void SetScale(Vec2 _vScale) { m_vColliderScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vColliderScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }

	UINT GetID() { return m_iID; }

	CCollider& operator = (CCollider& _other) = delete; // 대입연산자를 제거함

public:
	void finalUpdate();
	void render(HDC _dc);

public:
	// 충돌 시점 함수
	void OnCollision(CCollider* _pOther); // 충돌 중인 경우 호출되는 함수
	void OnCollisionEnter(CCollider* _pOther); // 이번에 충돌한 경우 호출되는 함수
	void OnCollisionExit(CCollider* _pOther); // 이번에 충돌에서 벗어나 ㄴ경우

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;

};

