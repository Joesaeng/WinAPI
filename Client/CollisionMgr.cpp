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

	map<ULONGLONG, bool>::iterator iter;
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

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();


			// 두 충돌제 조합 아이디 생성
			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// 충돌 정보가 미등록 상태인 경우 등록(충돌을 false로)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol))// 현재 충돌 중
			{

				if (iter->second) // 이전에도 충돌 하고 있었고 현재 충돌 중이다.
				{
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				else // 이번에 충돌했다.(이전에는 충돌하지 않았다.)
				{
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);
					iter->second = true;
				}
			}
			else // 현재 충돌 중이 아니다.
			{
				if (iter->second) // 이전에는 충돌 하고 있었다.(현재는 충돌하고 있지 않다.)
				{
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
			}
		}
	}
}

bool CollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();

	if (abs(vLeftPos.x - vRightPos.x) < (vLeftScale.x + vRightScale.x) / 2.f
		&& abs(vLeftPos.y - vRightPos.y) < (vLeftScale.y + vRightScale.y) / 2.f)
	{
		return true;
	}
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


