#include "pch.h"
#include "CUI.h"
#include "CCamera.h"
#include "KeyMgr.h"
#include "CCore.h"
#include "CTexture.h"

#include "SelectGDI.h"

CUI::CUI(bool _bCamAff)
	:m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
	, m_pUITex(nullptr)
	, m_iImageIdx(0)
	, m_wText(0)
{
}

CUI::CUI(const CUI& _origin)
	: CObject(_origin)
	 , m_pParentUI(nullptr)
	 , m_bCamAffected(_origin.m_bCamAffected)
	 , m_bMouseOn(false)
	 , m_bLbtnDown(false)
	 , m_pUITex(_origin.m_pUITex)
	 , m_iImageIdx(_origin.m_iImageIdx)
	 , m_wText(_origin.m_wText)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}
void CUI::render(HDC _dc)
{
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}
	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, int(vPos.x)
			, int(vPos.y)
			, int(vPos.x + vScale.x)
			, int(vPos.y + vScale.y));
	}

	if (m_pUITex)
	{
		if (nullptr == m_pUITex || -1 == m_iImageIdx)
			return;

		UINT iWidth = m_pUITex->Width();
		UINT iHeight = m_pUITex->Height();

		UINT iMaxCol = iWidth / TILE_SIZE;
		UINT iMaxRow = iHeight / TILE_SIZE;

		UINT iCurRow = (UINT)m_iImageIdx / iMaxCol;
		UINT iCurCol = (UINT)m_iImageIdx % iMaxCol;

		if (iMaxRow < iCurRow)
			assert(nullptr && "이미지 범위를 벗어난 인덱스");

		
		TransparentBlt(_dc
			, (int)(vPos.x)
			, (int)(vPos.y)
			, (int)(vScale.x)
			, (int)(vScale.y)
			, m_pUITex->GetDC()
			, (int)(iCurCol * TILE_SIZE)
			, (int)(iCurRow * TILE_SIZE)
			, (int)(TILE_SIZE)
			, (int)(TILE_SIZE)
			, RGB(255, 0, 255));
	}
	render_Child(_dc);
}

void CUI::update()
{
	

	update_Child();
}

void CUI::finalUpdate()
{
	CObject::finalUpdate();

	// UI의 최종 목표를 구한다
	m_vFinalPos = GetPos();

	if (GetParent())
		m_vFinalPos += GetParent()->GetFinalPos();

	
	// UI 마우스 체크
	MouseOnCheck();

	
	

	finalupdate_Child();
}

void CUI::update_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate_Child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalUpdate();
	}
}

void CUI::render_Child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();
	if (m_bCamAffected)
	{
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}
	if (m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x
		&& m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y)
	{
		m_bMouseOn = true;
	}
	else
	{
		m_bMouseOn = false;
	}
}

void CUI::MouseOn()
{
	
}

void CUI::MouseLBtnDown()
{
	
}

void CUI::MouseLBtnUp()
{

}

void CUI::MouseLBtnClicked()
{
}

