#include "pch.h"
#include "CScene_Tool.h"

#include "CScene.h"
#include "KeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"

#include "resource.h"

CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	// 타일 생성
	CreateTile(5,5);

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

	SetTileIdx();
	
}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		UINT iTileX = GetTileX();
		UINT iTileY = GetTileY();

		UINT iCol = (UINT)vMousePos.x / TILE_SIZE;
		UINT iRow = (UINT)vMousePos.y / TILE_SIZE;

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}
}




// ======================
// Tile Count Window Proc
// ======================
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK)
		{
			UINT iXcount = GetDlgItemInt(hDlg, IDC_XCOUNT, nullptr, false);
			UINT iYcount = GetDlgItemInt(hDlg, IDC_YCOUNT, nullptr, false);

			CScene* pCurScene = SceneMgr::GetInst()->GetCurScene();

			// ToolScene 확인
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXcount, iYcount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
	}
		break;
	}
	return (INT_PTR)FALSE;
}