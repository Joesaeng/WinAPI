#include "pch.h"
#include "CTitleUI.h"
#include "KeyMgr.h"


CTitleUI::CTitleUI()
	:CUI(false)
{
}

CTitleUI::~CTitleUI()
{
}

void CTitleUI::update()
{
}

void CTitleUI::render(HDC _dc)
{
	CUI::render(_dc);
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	RECT rt = { (LONG)vPos.x, (LONG)vPos.y, (LONG)(vPos.x + vScale.x), (LONG)(vPos.y + vScale.y) };
	if (GetUIText())
		DrawText(_dc, GetUIText(), -1, &rt, DT_CENTER | DT_TOP);
}

void CTitleUI::MouseOn()
{
	if (IsLbtnDown())
	{
		Vec2 vDiff = MOUSE_POS - m_vDragStart; // 마우스가 드래그한 거리

		Vec2 vCurPos = GetPos();
		vCurPos += vDiff; // 현재 포지션에 마우스 드래그 거리 증가
		SetPos(vCurPos); // 그 거리만큼 셋포지션

		m_vDragStart = MOUSE_POS; // 마우스 좌표 초기화
	}
}

void CTitleUI::MouseLBtnDown()
{
	m_vDragStart = MOUSE_POS; // 드래그를 시작한 시점의 마우스 좌표
}

void CTitleUI::MouseLBtnUp()
{
}

void CTitleUI::MouseLBtnClicked()
{
}


