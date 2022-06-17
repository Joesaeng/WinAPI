#include "pch.h"
#include "CollisionMgr.h"

#include "SceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CollisionMgr::CollisionMgr()
	: m_arrCheak{}
{}
CollisionMgr::~CollisionMgr()
{}


void CollisionMgr::update()
{
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			if (m_arrCheak[iRow] & (1 << iCol))
			{
				CollisionGroupUpdate((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}


}

void CollisionMgr::CollisionGroupUpdate(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	CScene* pCurScene =  SceneMgr::GetInst()->GetCurScene();

	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eLeft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eRight);

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// Collider가 없는 오브젝트를 받아온 경우
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// Collider가 없는 오브젝트이거나, 자기 자신과의 충돌인 경우
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
				continue;

			if (IsCollision(vecLeft[i]->GetCollider(), vecRight[j]->GetCollider()))
			{

			}
			else
			{

			}
		}
	}
}

bool CollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{

	return false;
}

void CollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eRight)
{
	// 더 작은 값의 그룹 타입을 행으로,
	// 큰 값을 열(비트)로 사용한다.
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	if (m_arrCheak[iRow] & (1 << iCol)) // 이미 그 자리가 체크되어 있다면
	{
		m_arrCheak[iRow] &= ~(1 << iCol); // 체크를 해제한다
	}
	else
	{
		m_arrCheak[iRow] |= (1 << iCol); // iRow 행에 iCol 열 자리에 1을 비트연산으로 넣어준다
	}

}


