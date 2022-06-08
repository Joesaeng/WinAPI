#include "pch.h"
#include "CCore.h"
#include "CObject.h"


CObject g_obj;


CCore::CCore()
	: m_hwnd(0)
	, m_ptResolution{}
	, m_hdc(0)
{

}
CCore::~CCore()
{
	ReleaseDC(m_hwnd, m_hdc);
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

	g_obj.m_ptPos = POINT{ m_ptResolution.x/2, m_ptResolution.y/2 };
	g_obj.m_ptScale = POINT{ 100,100 };

	return S_OK;
}


void CCore::progress()
{
	static int callCount = 0;
	++callCount;

	static int iPrevCount = GetTickCount();
	int iCurCount = GetTickCount();

	if (iCurCount - iPrevCount > 1000)
	{
		iPrevCount = iCurCount;
		callCount = 0;
	}

	update();

	render();
}

void CCore::update()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		g_obj.m_ptPos.x -= 1;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		g_obj.m_ptPos.x += 1;
	}
}

void CCore::render()
{
	// 그리기
	Rectangle(m_hdc, g_obj.m_ptPos.x - g_obj.m_ptScale.x / 2
					, g_obj.m_ptPos.y - g_obj.m_ptScale.y / 2
					, g_obj.m_ptPos.x + g_obj.m_ptScale.x / 2
					, g_obj.m_ptPos.y + g_obj.m_ptScale.y / 2 );

}
