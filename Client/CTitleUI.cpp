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
		Vec2 vDiff = MOUSE_POS - m_vDragStart; // ���콺�� �巡���� �Ÿ�

		Vec2 vCurPos = GetPos();
		vCurPos += vDiff; // ���� �����ǿ� ���콺 �巡�� �Ÿ� ����
		SetPos(vCurPos); // �� �Ÿ���ŭ ��������

		m_vDragStart = MOUSE_POS; // ���콺 ��ǥ �ʱ�ȭ
	}
}

void CTitleUI::MouseLBtnDown()
{
	m_vDragStart = MOUSE_POS; // �巡�׸� ������ ������ ���콺 ��ǥ
}

void CTitleUI::MouseLBtnUp()
{
}

void CTitleUI::MouseLBtnClicked()
{
}


