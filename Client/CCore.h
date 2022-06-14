#pragma once

class CCore
{
	SINGLE(CCore);
private:
	HWND	m_hwnd;			// 메인 윈도우 핸들
	POINT	m_ptResolution; // 메인 윈도우 해상도
	HDC		m_hdc;			// 메인 윈도우에 Draw 할 DC

	HBITMAP m_hBit;
	HDC		m_memDC;

public:
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

public:
	HWND GetMainHwnd() { return m_hwnd; }
	POINT GetResolution() { return m_ptResolution; }

};

