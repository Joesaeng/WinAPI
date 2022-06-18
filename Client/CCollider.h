#pragma once

class CObject;

class CCollider
{
private:
	static UINT g_iNextID;

	CObject*	m_pOwner;			// Collider�� �����ϰ� �ִ� ������Ʈ
	Vec2		m_vOffsetPos;		// ������Ʈ�κ��� ������� ��ġ
	Vec2		m_vFinalPos;		// finalupdate ���� �� �����Ӹ��� ���
	Vec2		m_vColliderScale;	// �浹ü ũ��

	UINT		m_iID;				// �浹ü ������ ID ��

public:
	void SetOffsetPos(Vec2 _vPos) {m_vOffsetPos = _vPos;}
	void SetScale(Vec2 _vScale) { m_vColliderScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vColliderScale; }

	UINT GetID() { return m_iID; }

	CCollider& operator = (CCollider& _other) = delete; // ���Կ����ڸ� ������

public:
	void finalUpdate();
	void render(HDC _dc);

public:
	// �浹 ���� �Լ�
	void OnCollision(CCollider* _pOther); // �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther); // �̹��� �浹�� ��� ȣ��Ǵ� �Լ�
	void OnCollisionExit(CCollider* _pOther); // �̹��� �浹���� ��� �����

public:
	CCollider();
	CCollider(const CCollider& _origin);
	~CCollider();

	friend class CObject;

};
