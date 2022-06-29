#include "pch.h"
#include "CPanelUI.h"
#include "KeyMgr.h"

#include "CTexture.h"
#include "ResourceMgr.h"
#include "CTile.h"
#include "CScene.h"
#include "CBtnUI.h"

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

void CPanelUI::CreateTileUI()
{
	CTexture* pTileTex = ResourceMgr::GetInst()->LoadTexture(L"Tile", L"texture\\tile\\mytile.bmp");
	UINT height = pTileTex->Height() / TILE_SIZE;
	UINT width = pTileTex->Width() / TILE_SIZE;
	UINT index = 0;

	// Ÿ�� ����
	for (UINT i = 0; i < height; ++i)
	{
		for (UINT j = 0; j < width; ++j)
		{
			CBtnUI* pTileBtn = new CBtnUI;
			
			wstring toIndex = std::to_wstring(index);
			pTileBtn->SetPos(Vec2(((float)j * TILE_SIZE), ((float)i * TILE_SIZE)));
			pTileBtn->SetName(L"Tileindex" + toIndex);
			pTileBtn->SetScale(Vec2(TILE_SIZE, TILE_SIZE));
			pTileBtn->SetTexture(pTileTex);
			pTileBtn->SetImgIdx(index++);

			AddChild(pTileBtn);
		}
	}
}

void CPanelUI::MouseOn()
{
	//if (IsLbtnDown())
	//{
	//	Vec2 vDiff =  MOUSE_POS - m_vDragStart; // ���콺�� �巡���� �Ÿ�

	//	Vec2 vCurPos = GetPos(); 
	//	vCurPos += vDiff; // ���� �����ǿ� ���콺 �巡�� �Ÿ� ����
	//	SetPos(vCurPos); // �� �Ÿ���ŭ ��������

	//	m_vDragStart = MOUSE_POS; // ���콺 ��ǥ �ʱ�ȭ
	//}
}

void CPanelUI::MouseLBtnDown()
{
	//m_vDragStart = MOUSE_POS; // �巡�׸� ������ ������ ���콺 ��ǥ
}

void CPanelUI::MouseLBtnUp()
{
}

void CPanelUI::MouseLBtnClicked()
{
}
