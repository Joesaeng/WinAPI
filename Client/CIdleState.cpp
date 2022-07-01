#include "pch.h"
#include "CIdleState.h"

#include "SceneMgr.h"
#include "CScene.h"

#include "CPlayer.h"
#include "CMonster.h"


CIdleState::CIdleState()
	: CState(MON_STATE::IDLE)
{
}

CIdleState::~CIdleState()
{
}

void CIdleState::update()
{
	// Player 의 위치 체크
	CPlayer* pPlayer = (CPlayer*)SceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// 몬스터의 범위 안에 들어오면 추적상태로 전환
	CMonster* pMonster = GetMonster();
	Vec2 vMonsterPos = pMonster->GetPos();

	// 플레이어와 몬스터 사이의 거리 구함
	Vec2 vDiff = vPlayerPos - vMonsterPos; 
	float fLen = vDiff.Length();		

	// 플레이어가 몬스터의 인식번위 안으로 진입
	if (fLen < pMonster->GetMonsterInfo().fRecogRange)
	{
		ChangeAIState(GetAI(), MON_STATE::TRACE);
	}
}

void CIdleState::Enter()
{
}

void CIdleState::Exit()
{
}


