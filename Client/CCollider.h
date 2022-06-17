#pragma once

class CObject;

class CCollider
{
private:
	CObject*	m_pOwner; // Collider를 소유하고 있는 오브젝트
	Vec2		m_vOffsetPos; // 오브젝트로부터 상대적인 위치
	Vec2		m_vFinalPos; // finalupdate 에서 매 프레임마다 계산
	Vec2		m_vColliderScale; // 충돌체 크기

public:
	void SetOffsetPos(Vec2 _vPos) {m_vOffsetPos = _vPos;}
	void SetScale(Vec2 _vScale) { m_vColliderScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vColliderScale; }


public:
	void finalUpdate();
	void render(HDC _dc);

public:
	CCollider();
	~CCollider();

	friend class CObject;

};

