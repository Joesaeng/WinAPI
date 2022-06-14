#include "pch.h"
#include "CMissile.h"

#include "TimeMgr.h"

CMissile::CMissile()
	:m_iDir(1.f)
{
}

CMissile::~CMissile()
{
}

void CMissile::update()
{
	Vec2 vPos = GetPos();

	vPos.y += 600.f * fDeltaTime * m_iDir;
	SetPos(vPos);
}

void CMissile::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	Vec2 vScale = GetScale();
	Ellipse(_dc, (int)vPos.x - vScale.x / 2.f, (int)vPos.y - vScale.y / 2.f,
				(int)vPos.x + vScale.x / 2.f, (int)vPos.y + vScale.y / 2.f);
}
