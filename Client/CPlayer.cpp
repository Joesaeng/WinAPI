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

static float hAxis;
static float vAxis;
static Vec2 prevDir;
static float atkDelay = 0.f;

CPlayer::CPlayer()
	: m_moveSpeed(200.f)
{
	// Texture 로딩
	// m_pTex = ResourceMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Run.bmp");
	SetName(L"Player");
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(32.f, 32.f));


	// Texture 로딩
	CTexture* pTex = ResourceMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\charAnim.bmp");
	CreateAnimator();
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 128.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"WALK_UP", pTex, Vec2(0.f, 192.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 6);
	GetAnimator()->CreateAnimation(L"IDLE_DOWN", pTex, Vec2(0.f, 256.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_UP", pTex, Vec2(64.f, 256.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_RIGHT", pTex, Vec2(128.f, 256.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1);
	GetAnimator()->CreateAnimation(L"IDLE_LEFT", pTex, Vec2(192.f, 256.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 1);
	GetAnimator()->Play(L"IDLE_DOWN", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	pAnim = GetAnimator()->FindAnimation(L"WALK_LEFT");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	pAnim = GetAnimator()->FindAnimation(L"WALK_RIGHT");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	pAnim = GetAnimator()->FindAnimation(L"WALK_UP");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
	GetAnimator()->FindAnimation(L"IDLE_UP")->GetFrame(0).vOffset = Vec2(0.f, -20.f);
	GetAnimator()->FindAnimation(L"IDLE_DOWN")->GetFrame(0).vOffset = Vec2(0.f, -20.f);
	GetAnimator()->FindAnimation(L"IDLE_LEFT")->GetFrame(0).vOffset = Vec2(0.f, -20.f);
	GetAnimator()->FindAnimation(L"IDLE_RIGHT")->GetFrame(0).vOffset = Vec2(0.f, -20.f);

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
	

	GetAnimator()->update();
	
}

void CPlayer::render(HDC _dc)
{
	component_render(_dc); // 컴포넌트(충돌체, etc ...)가 있는 경우 렌더
	/*CTexture* pTex = ResourceMgr::GetInst()->LoadTexture(L"PlayerTextex", L"texture\\charAnim.bmp");

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	float width = (float)pTex->Width();
	float height = (float)pTex->Height();
	
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = 127;

	AlphaBlend(_dc
		, int(vPos.x - width / 2.f)
		, int(vPos.y - height / 2.f)
		, (int)width, (int)height
		, pTex->GetDC()
		, 0, 0
		, (int)width, (int)height
		, bf);*/
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
	pMissile->SetDir(Vec2(m_dir.x, m_dir.y));
	pMissile->SetDmg(5);

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);
	atkDelay = 0.f;
	

}

void CPlayer::MovePlayer()
{
	Vec2 vPos = GetPos();


	if (KEY_HOLD(KEY::W))
	{
		hAxis = -1.f;
		GetAnimator()->Play(L"WALK_UP", true);
	}
	if (KEY_HOLD(KEY::S))
	{
		hAxis = 1.f;
		GetAnimator()->Play(L"WALK_DOWN", true);
	}
	if (KEY_HOLD(KEY::A))
	{
		vAxis = -1.f;
		GetAnimator()->Play(L"WALK_LEFT", true);
	}
	if (KEY_HOLD(KEY::D))
	{
		vAxis = 1.f;
		GetAnimator()->Play(L"WALK_RIGHT", true);
	}
	if (KEY_HOLD(KEY::SPACE))
	{
		CreateMissile();
	}
	if (KEY_AWAY(KEY::W))
	{
		hAxis = 0.f;
		GetAnimator()->Play(L"IDLE_UP", true);
	}
	if (KEY_AWAY(KEY::S))
	{
		hAxis = 0.f;
		GetAnimator()->Play(L"IDLE_DOWN", true);
	}
	if (KEY_AWAY(KEY::A))
	{
		vAxis = 0.f;
		GetAnimator()->Play(L"IDLE_LEFT", true);
	}
	if (KEY_AWAY(KEY::D))
	{
		vAxis = 0.f;
		GetAnimator()->Play(L"IDLE_RIGHT", true);
	}

	if (m_dir != Vec2(0.f, 0.f))
	{
		if (vAxis != 0.f || hAxis != 0.f)
			m_dir = Vec2(vAxis, hAxis);
		prevDir = m_dir;
	}
	else
		m_dir = prevDir;

	vPos += Vec2(vAxis, hAxis) * fDeltaTime * m_moveSpeed;
	SetPos(vPos);
}


