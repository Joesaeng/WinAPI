#include "pch.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "KeyMgr.h"

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

	CTimeMgr::GetInst()->init();
	KeyMgr::GetInst()->init();

	g_obj.SetPos(Vec2(m_ptResolution.x / 2, m_ptResolution.y / 2));
	g_obj.SetScale(Vec2(100,100));

	return S_OK;
}


void CCore::progress()
{
	// Manager Update
	CTimeMgr::GetInst()->update();


	update();

	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		vPos.x -= 100.f * fDT;
	}
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		vPos.x += 100.f * fDT;
	}

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_hdc,  (int)(vPos.x - vScale.x / 2.f)
					, (int)(vPos.y - vScale.y / 2.f)
					, (int)(vPos.x + vScale.x / 2.f)
					, (int)(vPos.y + vScale.y / 2.f));

}
