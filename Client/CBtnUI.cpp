#include "pch.h"
#include "CBtnUI.h"


CBtnUI::CBtnUI()
	: CUI(false)
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLBtnDown()
{
}

void CBtnUI::MouseLBtnUp()
{
}

void CBtnUI::MouseLBtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1, m_param2);
	}
}