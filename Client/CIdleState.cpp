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
	// Player �� ��ġ üũ
	CPlayer* pPlayer = (CPlayer*)SceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerPos = pPlayer->GetPos();

	// ������ ���� �ȿ� ������ �������·� ��ȯ
	CMonster* pMonster = GetMonster();
	Vec2 vMonsterPos = pMonster->GetPos();

	// �÷��̾�� ���� ������ �Ÿ� ����
	Vec2 vDiff = vPlayerPos - vMonsterPos; 
	float fLen = vDiff.Length();		

	// �÷��̾ ������ �νĹ��� ������ ����
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


