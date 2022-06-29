#include "pch.h"
#include "CBtnUI.h"
#include "CTexture.h"

CBtnUI::CBtnUI()
	: CUI(false)
	, m_pFunc(nullptr)
	, m_param1(0)
	, m_param2(0)
	, m_pSceneFunc(nullptr)
	, m_pSceneInst(nullptr)
	, m_index(-1)
{
}

CBtnUI::~CBtnUI()
{
}

void CBtnUI::render(HDC _dc)
{
	CUI::render(_dc);
	Vec2 vPos = GetPos() + GetParent()->GetPos() + GetParent()->GetParent()->GetPos();
	Vec2 vScale = GetScale();
	RECT rt = { (LONG)vPos.x, (LONG)vPos.y, (LONG)(vPos.x + vScale.x), (LONG)(vPos.y + vScale.y) };

	if (GetUIText())
		DrawText(_dc, GetUIText(), -1, &rt, DT_CENTER);
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
	if (m_pSceneFunc && m_pSceneInst)
	{
		(m_pSceneInst->*m_pSceneFunc)();
	}
	
}

