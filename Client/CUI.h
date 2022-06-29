#pragma once
#include "CObject.h"

class CTexture;

class CUI :
	public CObject
{
private:
	vector<CUI*>        m_vecChildUI;
	CUI*				m_pParentUI;
	Vec2                m_vFinalPos;


	bool				m_bCamAffected; // UI�� ī�޶� ������ �޴��� ����
	bool				m_bMouseOn;		// UI���� ���콺�� �ִ���
	bool				m_bLbtnDown;	// UI�� ���ʹ�ư�� �������� �ִ���

	LPCWSTR         m_wText;

	CTexture*	m_pUITex;
	UINT         m_iImageIdx;


public:
	Vec2 GetFinalPos() { return m_vFinalPos; }
	CUI* GetParent() { return m_pParentUI; }
	bool IsMouseOn() { return m_bMouseOn; }
	bool IsLbtnDown() { return m_bLbtnDown; }

	void SetUIText(LPCWSTR _text){m_wText = _text;}
	LPCWSTR GetUIText() {return m_wText;}
	void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }
	const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

public:
	void SetTexture(CTexture* _pTex)
	{
		m_pUITex = _pTex;
	}

	void AddImgIdx() { ++m_iImageIdx; }
	void SetImgIdx(UINT _index) { m_iImageIdx = _index; }
	
	UINT GetIndex() {return m_iImageIdx;}

public:
	virtual void update();
	virtual void finalUpdate();
	virtual void render(HDC _dc);

	virtual CUI* Clone() = 0;

private:
	void update_Child();
	void finalupdate_Child();
	void render_Child(HDC _dc);

	void MouseOnCheck();

public:
	virtual void MouseOn();

	virtual void MouseLBtnDown();
	virtual void MouseLBtnUp();
	virtual void MouseLBtnClicked();

	

public:
	CUI(bool _bCamAff);
	CUI(const CUI& _origin);
	virtual ~CUI();

	friend class UIMgr;
};

