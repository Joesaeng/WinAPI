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

CCore::CCore()
	: m_hwnd(0)
	, m_ptResolution{}
	, m_hdc(0)
	, m_hBit(0)
	, m_memDC(0)
	, m_arrBrush{}
	, m_arrPen{}
{
}
CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hdc);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}
int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// �ػ󵵿� �°� ������ ũ�� ����
	RECT rt = {0,0,m_ptResolution.x,m_ptResolution.y};
	AdjustWindowRect(&rt,WS_OVERLAPPEDWINDOW,true);
	SetWindowPos(m_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hdc = GetDC(m_hwnd);

	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����.
	m_hBit = CreateCompatibleBitmap(m_hdc, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hdc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);

	CreateBrushPen(); // ���� ����� �� �� �귯�� ����

	// Manager �ʱ�ȭ
	TimeMgr::MgrINIT;
	KeyMgr::MgrINIT;
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
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// SceneMgr ����
	SceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hdc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);
	TimeMgr::GetInst()->render(); // ������ ���̺� ������ ���

	// =============
	// �̺�Ʈ ����ó��
	// =============

	EventMgr::MgrUPDATE;
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

	// blue, green, red pen Create
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

}



	
