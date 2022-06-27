#include "pch.h"
#include "CPanelUI.h"
#include "KeyMgr.h"


CPanelUI::CPanelUI()
	: CUI(false)
{
}

CPanelUI::~CPanelUI()
{
}

void CPanelUI::update()
{
}

void CPanelUI::render(HDC _dc)
{
	CUI::render(_dc);
}

void CPanelUI::MouseOn()
{
	if (IsLbtnDown())
	{
		Vec2 vDiff =  MOUSE_POS - m_vDragStart; // 마우스가 드래그한 거리

		Vec2 vCurPos = GetPos(); 
		vCurPos += vDiff; // 현재 포지션에 마우스 드래그 거리 증가
		SetPos(vCurPos); // 그 거리만큼 셋포지션

		m_vDragStart = MOUSE_POS; // 마우스 좌표 초기화
	}
}

void CPanelUI::MouseLBtnDown()
{
	m_vDragStart = MOUSE_POS; // 드래그를 시작한 시점의 마우스 좌표
}

void CPanelUI::MouseLBtnUp()
{
}

void CPanelUI::MouseLBtnClicked()
{
}
