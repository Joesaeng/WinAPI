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
		// Collider�� ���� ������Ʈ�� �޾ƿ� ���
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// Collider�� ���� ������Ʈ�̰ų�, �ڱ� �ڽŰ��� �浹�� ���
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
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ)�� ����Ѵ�.
	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eRight;
	if (iCol < iRow)
	{
		iRow = (UINT)_eRight;
		iCol = (UINT)_eLeft;
	}
	if (m_arrCheak[iRow] & (1 << iCol)) // �̹� �� �ڸ��� üũ�Ǿ� �ִٸ�
	{
		m_arrCheak[iRow] &= ~(1 << iCol); // üũ�� �����Ѵ�
	}
	else
	{
		m_arrCheak[iRow] |= (1 << iCol); // iRow �࿡ iCol �� �ڸ��� 1�� ��Ʈ�������� �־��ش�
	}

}


