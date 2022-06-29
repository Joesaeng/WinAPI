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

	// 타일 생성
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
	//	Vec2 vDiff =  MOUSE_POS - m_vDragStart; // 마우스가 드래그한 거리

	//	Vec2 vCurPos = GetPos(); 
	//	vCurPos += vDiff; // 현재 포지션에 마우스 드래그 거리 증가
	//	SetPos(vCurPos); // 그 거리만큼 셋포지션

	//	m_vDragStart = MOUSE_POS; // 마우스 좌표 초기화
	//}
}

void CPanelUI::MouseLBtnDown()
{
	//m_vDragStart = MOUSE_POS; // 드래그를 시작한 시점의 마우스 좌표
}

void CPanelUI::MouseLBtnUp()
{
}

void CPanelUI::MouseLBtnClicked()
{
}
