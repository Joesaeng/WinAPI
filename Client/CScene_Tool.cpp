#include "pch.h"
#include "CScene_Tool.h"

#include "CScene.h"
#include "KeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "ResourceMgr.h"


CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	CTexture* pTileTex = ResourceMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\tile.bmp");

	// 타일 생성
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(Vec2((float)j * TILE_SIZE, (float)i * TILE_SIZE));
			pTile->SetTexture(pTileTex);
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
	// Camera Look 지정
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
}

void CScene_Tool::update()
{
	CScene::update();

}


