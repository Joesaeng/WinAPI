#include "pch.h"
#include "CCollider.h"
#include "CObject.h"
#include "CCore.h"

#include "SelectGDI.h"

UINT CCollider::g_iNextID = 0;

CCollider::CCollider()
	: m_pOwner(nullptr)
	, m_iID(g_iNextID++)
{
}

CCollider::~CCollider()
{
}

void CCollider::finalUpdate()
{
	// Object 의 위치를 따라간다.
	Vec2 vObjectPos = m_pOwner->GetPos();
	m_vFinalPos = vObjectPos + m_vOffsetPos;

}

void CCollider::render(HDC _dc)
{
	SelectGDI p(_dc, PEN_TYPE::GREEN);
	SelectGDI b(_dc, BRUSH_TYPE::HOLLOW);

	Rectangle(_dc
		, int(m_vFinalPos.x - m_vColliderScale.x / 2.f)
		, int(m_vFinalPos.y - m_vColliderScale.y / 2.f)
		, int(m_vFinalPos.x + m_vColliderScale.x / 2.f)
		, int(m_vFinalPos.y + m_vColliderScale.y / 2.f));
}


