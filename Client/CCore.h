#pragma once

class CTexture;

class CCore
{
	SINGLE(CCore);
private:
	HWND	m_hwnd;			// ���� ������ �ڵ�
	POINT	m_ptResolution; // ���� ������ �ػ�
	HDC		m_hdc;			// ���� �����쿡 Draw �� DC

	CTexture* m_pMemTex;	// ����� �ؽ���

	// ���� ����ϴ� GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];

	// �޴�
	HMENU	m_hMenu; // Tool Scene ������ ���

public:
	int init(HWND _hwnd, POINT _ptResolution);
	void progress();

private:
	void Clear();
	void CreateBrushPen();

public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _Resolution, bool _bMenu);

public:
	HWND GetMainHwnd() { return m_hwnd; }
	HDC GetMainDC() { return m_hdc; }
	POINT GetResolution() { return m_ptResolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};

