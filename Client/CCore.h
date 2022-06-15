#pragma once

class CCore
{
	SINGLE(CCore);
private:
	HWND	m_hwnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution; // ���� ������ �ػ�
	HDC		m_hdc;			// ���� �����쿡 Draw �� DC

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
	HDC GetMainDC() { return m_hdc; }
	POINT GetResolution() { return m_ptResolution; }

};

