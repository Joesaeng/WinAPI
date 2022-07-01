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

	// �ػ󵵿� �°� ������ ũ�� ����
	ChangeWindowSize(Vec2((float)_ptResolution.x,(float)_ptResolution.y),false);

	// �޴��� ����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCEW(IDC_CLIENT));

	m_hdc = GetDC(m_hwnd);

	// ���� ���۸� �뵵�� �ؽ��� ������ �����.
	m_pMemTex = ResourceMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptResolution.x, (UINT)m_ptResolution.y);

	CreateBrushPen(); // ���� ����� �� �� �귯�� ����


	// Manager �ʱ�ȭ
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

	// �浹üũ
	CollisionMgr::MgrUPDATE;

	// UI �̺�Ʈ üũ
	UIMgr::MgrUPDATE;

	// =========
	// Rendering
	// =========
	
	// ȭ�� Clear
	Clear();
	
	// SceneMgr ����
	SceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hdc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_pMemTex->GetDC(), 0, 0, SRCCOPY);
	TimeMgr::GetInst()->render(); // ������ ���̺� ������ ���

	// =============
	// �̺�Ʈ ����ó��
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
	// Tool Scene ������ ����� �޴� ����
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



	
