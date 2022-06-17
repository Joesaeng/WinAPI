#pragma once

class CCollider;

class CollisionMgr
{
	SINGLE(CollisionMgr);
private:
	// 충돌체 간의 이전 프레임 충돌 정보
	UINT m_arrCheak[(UINT)GROUP_TYPE::END]; // 그룹간의 충돌 체크 매트릭스

public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight);
	void Reset(){memset(m_arrCheak, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);}

private:
	void CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight );
	bool IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol);
};

