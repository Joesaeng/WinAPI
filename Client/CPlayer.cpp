#include "pch.h"
#include "CPlayer.h"

#include "CScene.h"
#include "KeyMgr.h"
#include "TimeMgr.h"
#include "SceneMgr.h"
#include "PathMgr.h"
#include "ResourceMgr.h"

#include "CMissile.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"

static float hAxis;
static float vAxis;
static Vec2 prevDir;
static float atkDelay = 0.f;

CPlayer::CPlayer()
	: m_moveSpeed(200.f)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_iDir(1)
	, m_ipDir(1)
{
	// Texture 로딩
	// m_pTex = ResourceMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Run.bmp");
	SetName(L"Player");
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(32.f, 64.f));

	CreateRigidBody(1.f);
	GetRigidBody()->SetMaxSpeed(200.f);

	// Texture 로딩
	//CTexture* pTex = ResourceMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\charAnim.bmp");
	CTexture* pTex = ResourceMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\charAnimVertical.bmp");
	CreateAnimator();

	/*GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 128.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WALK_UP", pTex, Vec2(0.f, 192.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"IDLE_DOWN", pTex, Vec2(0.f, 256.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_UP", pTex, Vec2(64.f, 256.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(128.f, 256.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(192.f, 256.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1);
	GetAnimator()->Play(L"IDLE_DOWN", true);*/

	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f,64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6);

	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(0.f, 128.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(64.f, 128.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1);
	/*for (size_t i = 0; i < GetAnimator()->FindAnimation(L"WALK_UP")->GetMaxFrame(); ++i)
	{
		GetAnimator()->FindAnimation(L"WALK_UP")->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	for (size_t i = 0; i < GetAnimator()->FindAnimation(L"WALK_LEFT")->GetMaxFrame(); ++i)
	{
		GetAnimator()->FindAnimation(L"WALK_LEFT")->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	for (size_t i = 0; i < GetAnimator()->FindAnimation(L"WALK_RIGHT")->GetMaxFrame(); ++i)
	{
		GetAnimator()->FindAnimation(L"WALK_RIGHT")->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	for (size_t i = 0; i < GetAnimator()->FindAnimation(L"WALK_DOWN")->GetMaxFrame(); ++i)
	{
		GetAnimator()->FindAnimation(L"WALK_DOWN")->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	GetAnimator()->FindAnimation(L"IDLE_UP")->GetFrame(0).vOffset = Vec2(0.f, -20.f);
	GetAnimator()->FindAnimation(L"IDLE_DOWN")->GetFrame(0).vOffset = Vec2(0.f, -20.f);
	GetAnimator()->FindAnimation(L"IDLE_LEFT")->GetFrame(0).vOffset = Vec2(0.f, -20.f);
	GetAnimator()->FindAnimation(L"IDLE_RIGHT")->GetFrame(0).vOffset = Vec2(0.f, -20.f);*/

	CreateGravity();

	m_dir = Vec2(0.f, 1.f);
	prevDir = m_dir;
}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	if (0.21f >= atkDelay)
		atkDelay += fDeltaTime;

	MovePlayer();
	update_state();
	update_animation();

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
	m_ipDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	component_render(_dc); // 컴포넌트(충돌체, etc ...)가 있는 경우 렌더
}

void CPlayer::CreateMissile()
{
	if (0.2f >= atkDelay)
		return;

	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= (GetScale().y / 2.f) - 20.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetName(L"Missile_Player");
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2((float)m_iDir,0.f));
	pMissile->SetDmg(5);

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
	atkDelay = 0.f;


}

void CPlayer::update_state()
{
	if (0.f != GetRigidBody()->GetSpeed())
	{
		if (KEY_HOLD(KEY::A))
		{
			m_iDir = -1;
			m_eCurState = PLAYER_STATE::WALK;
		}
		if (KEY_HOLD(KEY::D))
		{
			m_iDir = 1;
			m_eCurState = PLAYER_STATE::WALK;
		}
		if (KEY_HOLD(KEY::A) && KEY_HOLD(KEY::D))
		{
			m_iDir = m_ipDir;
		}
	}
	else
	{
		m_eCurState = PLAYER_STATE::IDLE;
	}
}

void CPlayer::update_animation()
{
	if (m_ePrevState == m_eCurState && m_ipDir == m_iDir)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
		if (m_iDir == 1)
			GetAnimator()->Play(L"IDLE_RIGHT",true);
		else
			GetAnimator()->Play(L"IDLE_LEFT",true);
		break;
	case PLAYER_STATE::WALK:
		if (m_iDir == 1)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else
			GetAnimator()->Play(L"WALK_LEFT", true);
		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	case PLAYER_STATE::HIT:

		break;
	}
}

void CPlayer::MovePlayer()
{
	CRigidBody* pRigid = GetRigidBody();

	/*if (KEY_HOLD(KEY::W))
	{
		hAxis = -1.f;
		GetAnimator()->Play(L"WALK_UP", true);
	}
	if (KEY_HOLD(KEY::S))
	{
		hAxis = 1.f;
		GetAnimator()->Play(L"WALK_DOWN", true);
	}*/
	if (KEY_HOLD(KEY::A))
	{
		vAxis = -1.f;
	}
	if (KEY_HOLD(KEY::D))
	{
		vAxis = 1.f;
	}
	if (KEY_HOLD(KEY::A) && KEY_HOLD(KEY::D))
	{
		vAxis = 0.f;
	}
	/*if (KEY_TAP(KEY::W))
	{
		pRigid->AddVelocity(Vec2(0.f,-100.f));
	}
	if (KEY_TAP(KEY::S))
	{
		pRigid->AddVelocity(Vec2(0.f, 100.f));
	}*/
	if (KEY_TAP(KEY::A))
	{
		pRigid->AddVelocity(Vec2(-100.f,0.f));
	}
	if (KEY_TAP(KEY::D))
	{
		pRigid->AddVelocity(Vec2(100.f, 0.f));
	}
	/*if (KEY_AWAY(KEY::W))
	{
		hAxis = 0.f;
		GetAnimator()->Play(L"IDLE_UP", true);
	}
	if (KEY_AWAY(KEY::S))
	{
		hAxis = 0.f;
		GetAnimator()->Play(L"IDLE_DOWN", true);
	}*/
	if (KEY_NONE(KEY::A) && KEY_NONE(KEY::D))
	{
		vAxis = 0.f;
	}
	
	
	Vec2 vMoveForce = Vec2(vAxis, 0.f) * m_moveSpeed;
	pRigid->AddForce(vMoveForce);
}

//void CPlayer::MovePlayer() // 플레이어 이동(키입력 방식)
//{
//	Vec2 vPos = GetPos();
//
//
//	if (KEY_HOLD(KEY::W))
//	{
//		hAxis = -1.f;
//		GetAnimator()->Play(L"WALK_UP", true);
//	}
//	if (KEY_HOLD(KEY::S))
//	{
//		hAxis = 1.f;
//		GetAnimator()->Play(L"WALK_DOWN", true);
//	}
//	if (KEY_HOLD(KEY::A))
//	{
//		vAxis = -1.f;
//		GetAnimator()->Play(L"WALK_LEFT", true);
//	}
//	if (KEY_HOLD(KEY::D))
//	{
//		vAxis = 1.f;
//		GetAnimator()->Play(L"WALK_RIGHT", true);
//	}
//	if (KEY_HOLD(KEY::SPACE))
//	{
//		CreateMissile();
//	}
//	if (KEY_AWAY(KEY::W))
//	{
//		hAxis = 0.f;
//		GetAnimator()->Play(L"IDLE_UP", true);
//	}
//	if (KEY_AWAY(KEY::S))
//	{
//		hAxis = 0.f;
//		GetAnimator()->Play(L"IDLE_DOWN", true);
//	}
//	if (KEY_AWAY(KEY::A))
//	{
//		vAxis = 0.f;
//		GetAnimator()->Play(L"IDLE_LEFT", true);
//	}
//	if (KEY_AWAY(KEY::D))
//	{
//		vAxis = 0.f;
//		GetAnimator()->Play(L"IDLE_RIGHT", true);
//	}
//
//	if (m_dir != Vec2(0.f, 0.f))
//	{
//		if (vAxis != 0.f || hAxis != 0.f)
//			m_dir = Vec2(vAxis, hAxis);
//		prevDir = m_dir;
//	}
//	else
//		m_dir = prevDir;
//
//	vPos += Vec2(vAxis, hAxis) * fDeltaTime * m_moveSpeed;
//	SetPos(vPos);
//}


