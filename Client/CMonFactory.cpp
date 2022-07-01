#include "pch.h"
#include "CMonFactory.h"
#include "CMonster.h"
#include "CCollider.h"
#include "AI.h"

#include "CIdleState.h"
#include "CTraceState.h"


CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;

	switch (_eType)
	{
	case MON_TYPE::NORMAL:
	{
		pMon = new CMonster;
		pMon->SetPos(_vPos);
		pMon->SetName(L"NORMAL");
		pMon->SetScale(Vec2(100.f, 100.f));
		pMon->CreateCollider();
		pMon->GetCollider()->SetScale(Vec2(105.f, 105.f));

		tMonInfo info = {};
		info.fDamage = 10.f;
		info.fAtkRange = 50.f;
		info.fRecogRange = 300.f;
		info.fHP = 50.f;
		info.fSpeed = 80.f;

		pMon->SetMonInfo(info);

		AI* pAI = new AI;
		pAI->AddState(new CIdleState);
		pAI->AddState(new CTraceState);
		pAI->SetCurState(MON_STATE::IDLE);

		pMon->SetAI(pAI);
	}
		break;
	case MON_TYPE::RANGE:


		break;
	}

	assert(pMon && "몬스터 생성중에 몬스터 포인터가 nullptr을 반환합니다");
	return pMon;
}
