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
		Vec2 vDiff =  MOUSE_POS - m_vDragStart; // ���콺�� �巡���� �Ÿ�

		Vec2 vCurPos = GetPos(); 
		vCurPos += vDiff; // ���� �����ǿ� ���콺 �巡�� �Ÿ� ����
		SetPos(vCurPos); // �� �Ÿ���ŭ ��������

		m_vDragStart = MOUSE_POS; // ���콺 ��ǥ �ʱ�ȭ
	}
}

void CPanelUI::MouseLBtnDown()
{
	m_vDragStart = MOUSE_POS; // �巡�׸� ������ ������ ���콺 ��ǥ
}

void CPanelUI::MouseLBtnUp()
{
}

void CPanelUI::MouseLBtnClicked()
{
}
