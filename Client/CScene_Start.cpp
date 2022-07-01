#include "pch.h"
#include "CScene_Start.h"

#include "PathMgr.h"
#include "CollisionMgr.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"


CScene_Start::CScene_Start()
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	CScene::update();
	
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vLookat = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(vLookat);
	}
}

void CScene_Start::Enter()
{
	// Player Object 추가
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f,584.f));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	CCamera::GetInst()->SetTarget(pObj);

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(580.f, 584.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	// 몬스터 배치
	
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(640.f, 100.f));
	
	AddObject(pMon, GROUP_TYPE::MONSTER);

	// 타일 로딩
	//LoadTile(L"tile\\StartTile.tile");


	// 충돌 지정
	// Player 그룹과 Monster 그릅 간의 충돌체크
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	// Camera 효과 지정
	CCamera::GetInst()->CamEffect(CAM_EFFECT::FADE_OUT, 1.f);
	CCamera::GetInst()->CamEffect(CAM_EFFECT::FADE_IN, 1.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	CollisionMgr::GetInst()->Reset();
}