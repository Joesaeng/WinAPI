#include "pch.h"
#include "CScene.h"

#include "CObject.h"
#include "CCore.h"
#include "CTile.h"
#include "ResourceMgr.h"


CScene::CScene()
	:m_iTileX(0)
	, m_iTileY(0)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] �׷��� j ��ü ����
			delete m_arrObj[i][j];
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if(!m_arrObj[i][j]->IsDead()) // ������Ʈ�� isDead ���� üũ
				m_arrObj[i][j]->update();
		}
	}
}

void CScene::finalUpdate()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->finalUpdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		vector<CObject*>::iterator iter = m_arrObj[i].begin();
		for (; iter < m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead()) // ������Ʈ�� isDead ���� üũ
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	// Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]); * �Լ� ���ø��̱� ������ �������� �̷��� ���°� ���������� �����Ϸ��� �˾Ƽ� �ؼ����ش�.
	Safe_Delete_Vec(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXcount, UINT _iYcount)
{
	m_iTileX = _iXcount;
	m_iTileY = _iYcount;

	CTexture* pTileTex = ResourceMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\tile.bmp");
	// Ÿ�� ����
	for (UINT i = 0; i < _iYcount; ++i)
	{
		for (UINT j = 0; j < _iXcount; ++j)
		{
			CTile* pTile = new CTile();

			pTile->SetPos(Vec2((float)j * TILE_SIZE, (float)i * TILE_SIZE));
			pTile->SetTexture(pTileTex);

			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}
