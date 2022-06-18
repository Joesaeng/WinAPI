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
		// Collider�� ���� ������Ʈ�� �޾ƿ� ���
		if (nullptr == vecLeft[i]->GetCollider())
			continue;

		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// Collider�� ���� ������Ʈ�̰ų�, �ڱ� �ڽŰ��� �浹�� ���
			if (nullptr == vecRight[j]->GetCollider() || vecLeft[i] == vecRight[j])
				continue;

			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();


			// �� �浹�� ���� ���̵� ����
			COLLIDER_ID ID;
			ID.iLeft_id = pLeftCol->GetID();
			ID.iRight_id = pRightCol->GetID();

			iter = m_mapColInfo.find(ID.ID);

			// �浹 ������ �̵�� ������ ��� ���(�浹�� false��)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol))// ���� �浹 ��
			{

				if (iter->second) // �������� �浹 �ϰ� �־��� ���� �浹 ���̴�.
				{
					pLeftCol->OnCollision(pRightCol);
					pRightCol->OnCollision(pLeftCol);
				}
				else // �̹��� �浹�ߴ�.(�������� �浹���� �ʾҴ�.)
				{
					pLeftCol->OnCollisionEnter(pRightCol);
					pRightCol->OnCollisionEnter(pLeftCol);
					iter->second = true;
				}
			}
			else // ���� �浹 ���� �ƴϴ�.
			{
				if (iter->second) // �������� �浹 �ϰ� �־���.(����� �浹�ϰ� ���� �ʴ�.)
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


