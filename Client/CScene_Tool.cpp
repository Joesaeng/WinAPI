#include "pch.h"
#include "CScene_Tool.h"

#include "CScene.h"
#include "KeyMgr.h"
#include "CTile.h"
#include "CCore.h"
#include "ResourceMgr.h"
#include "SceneMgr.h"
#include "UIMgr.h"
#include "PathMgr.h"

#include "resource.h"
#include "CUI.h"
#include "CBtnUI.h"
#include "CPanelUI.h"
#include "CTitleUI.h"
#include "CCamera.h"

void changeScene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
	:m_pUI(nullptr)
	, m_index(0)
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	CCore::GetInst()->DockMenu();

	// 타일 생성
	CreateTile(5,5);

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// UI 하나 생성
	CUI* pTitleUI = new CTitleUI;
	pTitleUI->SetName(L"TitleUI");
	pTitleUI->SetScale(Vec2(300.f, 380.f));
	pTitleUI->SetUIText(TEXT("타일 만들기"));
	pTitleUI->SetPos(Vec2(vResolution.x - pTitleUI->GetScale().x, 0.f));

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"PanelUI");
	pPanelUI->SetScale(Vec2(300.f,350.f));
	pPanelUI->SetPos(Vec2(0, 30));
	pTitleUI->AddChild(pPanelUI);
	((CPanelUI*)pPanelUI)->CreateTileUI();
	
	vector<CUI*> vecPanelChild = pPanelUI->GetChildUI();
	for (size_t i = 0; i < vecPanelChild.size(); ++i)
	{
		UINT j = vecPanelChild[i]->GetIndex();
		((CBtnUI*)vecPanelChild[i])->SetClikedCallBack(this, (SCENE_MEMFUNC_UINT)&CScene_Tool::SetTileNum,j);
	}

	CBtnUI* pSaveBtnUI = new CBtnUI;
	pSaveBtnUI->SetName(L"SaveBtnUI");
	pSaveBtnUI->SetScale(Vec2(100.f, 30.f));
	pSaveBtnUI->SetPos(Vec2(20.f, 300.f));
	pSaveBtnUI->SetUIText(TEXT("SAVE"));
	pSaveBtnUI->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	pPanelUI->AddChild(pSaveBtnUI);

	CUI* pLoadBtnUI = pSaveBtnUI->Clone();
	pLoadBtnUI->SetName(L"LoadBtnUI");
	pLoadBtnUI->SetPos(Vec2(180.f, 300.f));
	pLoadBtnUI->SetUIText(TEXT("LOAD"));
	((CBtnUI*)pLoadBtnUI)->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::LoadTileData);
	pPanelUI->AddChild(pLoadBtnUI);

	CBtnUI* pSetAllTileBtnUI = new CBtnUI;
	pSetAllTileBtnUI->SetName(L"SetAllTileBtnUI");
	pSetAllTileBtnUI->SetScale(Vec2(200.f, 30.f));
	pSetAllTileBtnUI->SetPos(Vec2(50.f, 260.f));
	pSetAllTileBtnUI->SetUIText(TEXT("SETALL"));
	pSetAllTileBtnUI->SetClikedCallBack(this, (SCENE_MEMFUNC)&CScene_Tool::SetAllTile);
	pPanelUI->AddChild(pSetAllTileBtnUI);

	AddObject(pTitleUI, GROUP_TYPE::UI);

	//// 복사본 UI
	//CUI* pClonePanel = pPanelUI->Clone();
	//pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-500.f, 0.f));
	////((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClikedCallBack(changeScene, 0, 0); // 다운캐스팅
	//CBtnUI* pCloneBtn = dynamic_cast<CBtnUI*>(pClonePanel->GetChildUI()[0]);	  //  
	//pCloneBtn->SetClikedCallBack(changeScene, 0, 0);							  // 다이나믹 캐스팅
	//AddObject(pClonePanel, GROUP_TYPE::UI);

	//m_pUI = pClonePanel;

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
	CCore::GetInst()->DivideMenu();
	DeleteAll();
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

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();
		
		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (0.f > vMousePos.x || iTileX <= iCol
			|| 0.f > vMousePos.y || iTileX <= iRow)
			return;

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->SetImgIdx(m_index);
	}
}


void CScene_Tool::SetAllTile()
{
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->SetImgIdx(m_index);
	}
	
}

void CScene_Tool::SaveTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};


	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strFilePath = PathMgr::GetInst()->GetContentPath();
	strFilePath += L"tile";

	ofn.lpstrInitialDir = strFilePath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetSaveFileName(&ofn))
	{
		SaveTile(szName);
	}


	
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{
	// 커널 오브젝트
	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strFilePath.c_str(), L"wb"); // 바이너리 쓰기 모드로 열기
	assert(pFile);
	
	// 타일 가로세로 개수 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// 타일 각자의 정보 저장
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		((CTile*)vecTile[i])->Save(pFile);
	}


	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	wchar_t szName[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strFilePath = PathMgr::GetInst()->GetContentPath();
	strFilePath += L"tile";

	ofn.lpstrInitialDir = strFilePath.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal
	if (GetOpenFileName(&ofn))
	{
		wstring strRelativePath = PathMgr::GetInst()->GetRelativePath(szName);

		LoadTile(strRelativePath);
	}
}

void changeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
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