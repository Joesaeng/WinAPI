#include "pch.h"
#include "CTraceState.h"

#include "SceneMgr.h"
#include "CScene.h"
#include "CPlayer.h"
#include "TimeMgr.h"

#include "CMonster.h"

CTraceState::CTraceState()
	: CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}
void CTraceState::update()
{
	// Ÿ���� �� Player �� �����Ѵ�
	CPlayer* pPlayer = (CPlayer*)SceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	Vec2 vMonPos = GetMonster()->GetPos();

	Vec2 vMonDir = vPlayerPos - vMonPos;
	vMonDir.Normalize();

	vMonPos += vMonDir * GetMonster()->GetMonsterInfo().fSpeed * fDeltaTime;

	GetMonster()->SetPos(vMonPos);
}

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}



