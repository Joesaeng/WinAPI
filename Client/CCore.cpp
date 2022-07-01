#include "pch.h"
#include "CCore.h"
#include "CObject.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "CollisionMgr.h"
#include "UIMgr.h"
#include "EventMgr.h"
#include "CCamera.h"
#include "ResourceMgr.h"
#include "CTexture.h"
#include "SelectGDI.h"

#include "resource.h"

CCore::CCore()
	: m_hwnd(0)
	, m_ptResolution{}
	, m_hdc(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}
CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hdc);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}

	DestroyMenu(m_hMenu);
}


int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	ChangeWindowSize(Vec2((float)_ptResolution.x,(float)_ptResolution.y),false);

	// 메뉴바 생성
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	m_hdc = GetDC(m_hwnd);

	// 이중 버퍼링 용도의 텍스쳐 한장을 만든다.
	m_pMemTex = ResourceMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	CreateBrushPen(); // 자주 사용할 펜 및 브러쉬 생성


	// Manager 초기화
	TimeMgr::MgrINIT;
	KeyMgr::MgrINIT;
	CCamera::MgrINIT;
	PathMgr::MgrINIT;
	SceneMgr::MgrINIT;
	
	
	return S_OK;
}


void CCore::progress()
{
	// Manager Update
	TimeMgr::MgrUPDATE;
	KeyMgr::MgrUPDATE;
	CCamera::MgrUPDATE;
	// ============
	// Scene Update
	// ============
	SceneMgr::MgrUPDATE;

	// 충돌체크
	CollisionMgr::MgrUPDATE;

	// UI 이벤트 체크
	UIMgr::MgrUPDATE;

	// =========
	// Rendering
	// =========
	
	// 화면 Clear
	Clear();
	
	// SceneMgr 렌더
	SceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hdc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDC(), 0, 0, SRCCOPY);
	TimeMgr::GetInst()->render(); // 윈도우 테이블에 프레임 출력

	// =============
	// 이벤트 지연처리
	// =============

	EventMgr::MgrUPDATE;
}

void CCore::Clear()
{
	SelectGDI gdi(m_pMemTex->GetDC(), BRUSH_TYPE::BLACK);
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);


	// blue, green, red pen Create
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

}

void CCore::DockMenu()
{
	// Tool Scene 에서만 사용할 메뉴 생성
	SetMenu(m_hwnd,m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hwnd, nullptr);
	ChangeWindowSize(GetResolution(), false);
}

void CCore::ChangeWindowSize(Vec2 _Resolution, bool _bMenu)
{
	RECT rt = { 0,0,(LONG)_Resolution.x,(LONG)_Resolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	SetWindowPos(m_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
}



	
