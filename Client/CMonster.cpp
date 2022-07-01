#include "pch.h"
#include "CMonster.h"

#include "TimeMgr.h"
#include "SceneMgr.h"

#include "CMissile.h"
#include "CScene.h"
#include "CCollider.h"
#include "AI.h"


CMonster::CMonster()
	: m_tInfo{}
	,m_AI(nullptr)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (nullptr != m_AI)
		delete m_AI;
}



void CMonster::update()
{
	m_AI->update();
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Missile_Player")
	{
		isHit(_pOther->GetObj());
		if (0.f >= m_tInfo.fHP)
			DeleteObject(this);
	}
}

void CMonster::SetAI(AI* _pAI)
{
	m_AI = _pAI;
	m_AI->m_pOwner = this;
}

void CMonster::MonsterFire()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(10.f, 10.f));
	pMissile->SetDir(false);

	CScene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::PROJ_MONSTER);
}

void CMonster::isHit(CObject* _pHit)
{
	//CMissile* pMissile = dynamic_cast<CMissile*>(_pHit);
	//dmg = pMissile->GetDmg();
	Vec2 vMissilePos = _pHit->GetPos();
	Vec2 vDir = GetPos() - vMissilePos;
	vDir.Normalize();

	SetPos(GetPos() + vDir * 10.f);

	float dmg = ((CMissile*)_pHit)->GetDmg();
	m_tInfo.fHP -= dmg;
}