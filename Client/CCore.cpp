#include "pch.h"
#include "CCore.h"
#include "CObject.h"

#include "TimeMgr.h"
#include "KeyMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"


CCore::CCore()
	: m_hwnd(0)
	, m_ptResolution{}
	, m_hdc(0)
	, m_hBit(0)
	, m_memDC(0)
{
}
CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hdc);

	DeleteDC(m_memDC);
	DeleteObject(m_hBit);
}
int CCore::init(HWND _hwnd, POINT _ptResolution)
{
	m_hwnd = _hwnd;
	m_ptResolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = {0,0,m_ptResolution.x,m_ptResolution.y};
	AdjustWindowRect(&rt,WS_OVERLAPPEDWINDOW,true);
	SetWindowPos(m_hwnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hdc = GetDC(m_hwnd);

	// 이중 버퍼링 용도의 비트맵과 DC를 만든다.
	m_hBit = CreateCompatibleBitmap(m_hdc, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hdc);

	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);


	// Manager 초기화
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
	SceneMgr::MgrUPDATE;

	// =========
	// Rendering
	// =========

	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// SceneMgr 렌더
	SceneMgr::GetInst()->render(m_memDC);

	BitBlt(m_hdc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);
	//TimeMgr::GetInst()->render();
}



	
