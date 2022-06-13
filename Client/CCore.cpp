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
	KeyMgr::GetInst()->update();


	update();

	render();
}

void CCore::update()
{
	Vec2 vPos = g_obj.GetPos();
	
	if (KeyMgr::GetInst()->GetKeyState(KEY::LEFT) == KEY_STATE::HOLD)
	{
		vPos.x -= 100.f * fDeltaTime;
	}
	if (KeyMgr::GetInst()->GetKeyState(KEY::RIGHT) == KEY_STATE::HOLD)
	{
		vPos.x += 100.f * fDeltaTime;
	}
	

	g_obj.SetPos(vPos);
}

void CCore::render()
{
	// 화면 Clear
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);

	// 그리기
	Vec2 vPos = g_obj.GetPos();
	Vec2 vScale = g_obj.GetScale();

	Rectangle(m_memDC,  (int)(vPos.x - vScale.x / 2.f)
					, (int)(vPos.y - vScale.y / 2.f)
					, (int)(vPos.x + vScale.x / 2.f)
					, (int)(vPos.y + vScale.y / 2.f));


	BitBlt(m_hdc, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);
}
