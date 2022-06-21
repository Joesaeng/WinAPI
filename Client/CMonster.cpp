#include "pch.h"
#include "CMonster.h"

#include "TimeMgr.h"
#include "SceneMgr.h"

#include "CMissile.h"
#include "CScene.h"
#include "CCollider.h"


CMonster::CMonster()
	: m_vCenterPos(0.f,0.f)
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_iHP(15)
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
}



void CMonster::update()
{
	Vec2 vCurPos = GetPos();

	// ���� �������� �ð��� m_fSpeed ��ŭ �̵�
	vCurPos.x += fDeltaTime * m_fSpeed * m_iDir;

	// ��ȸ �Ÿ� ���ط��� �Ѿ���� Ȯ��
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance; // �ʰ���
	if (0.f < fDist)
	{
		// ���� ����
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Missile_Player")
	{
		isHit(_pOther->GetObj());
		if(0 >= m_iHP)
			DeleteObject(this);
	}
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
	CMissile* pMissile = dynamic_cast<CMissile*>(_pHit);
	UINT dmg = pMissile->GetDmg();
	m_iHP -= dmg;
}