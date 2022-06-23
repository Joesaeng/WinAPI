#include "pch.h"
#include "CMissile.h"

#include "TimeMgr.h"
#include "CCamera.h"

#include <cmath>

#include "CCollider.h"
CMissile::CMissile()
	: m_fTheta(PI / 4.f)
	, m_vDir(Vec2(1.f, 1.f))
	, m_deadCount(0.f)
	, m_iDmg(0)
{
	m_vDir.Normalize();
	CreateCollider();
	GetCollider()->SetScale(Vec2(15.f, 15.f));
}


CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	//vPos.x += 600.f * cosf(m_fTheta) * fDeltaTime;
	//vPos.y -= 600.f * sinf(m_fTheta) * fDeltaTime;

	vPos.x += 600.f * m_vDir.x * fDeltaTime;
	vPos.y += 600.f * m_vDir.y * fDeltaTime;


	SetPos(vPos);
	m_deadCount += fDeltaTime;
	if (2.f < m_deadCount)
	{
  		DeleteObject(this);
	}
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();

	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	Ellipse(_dc, int(vPos.x - vScale.x / 2.f), int(vPos.y - vScale.y / 2.f),
				int(vPos.x + vScale.x / 2.f), int(vPos.y + vScale.y / 2.f));

	component_render(_dc);
}

void CMissile::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Monster")
	{
		DeleteObject(this);
	}
}
