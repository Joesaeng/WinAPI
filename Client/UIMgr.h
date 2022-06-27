#include "pch.h"
#pragma once

class CUI;

class UIMgr
{
	SINGLE(UIMgr)

private:
	CUI*		m_pFocuseUI;

public:
	void update();

	void SetFocusedUI(CUI* _pUI);

private:
	// �θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.
	CUI* GetFocusedUI();
	CUI* GetTargetUI(CUI* _pParentUI);
};

