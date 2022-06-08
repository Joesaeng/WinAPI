#pragma once

class CCore
{
	SINGLE(CCore);
private:
	HWND	m_hwnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution; // ���� ������ �ػ�
	HDC		m_hdc;			// ���� �����쿡 Draw �� DC

public:
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();

private:
	void update();
	void render();

	CCore();
	~CCore();
};

