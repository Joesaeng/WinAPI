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

CPlayer::CPlayer()
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
	GetAnimator()->Play(L"WALK_DOWN", true);

	CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	for (size_t i = 0; i < pAnim->GetMaxFrame(); ++i)
	{
		pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);
	}
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDeltaTime;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDeltaTime;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDeltaTime;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDeltaTime;
	}
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}
	
	GetAnimator()->update();
	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{
	// component_render(_dc); // 컴포넌트(충돌체, etc ...)가 있는 경우 렌더
	CTexture* pTex = ResourceMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\player.bmp");

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	float width = (float)pTex->Width();
	float height = (float)pTex->Height();
	
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = AC_SRC_ALPHA;
	bf.SourceConstantAlpha = 255;

	AlphaBlend(_dc
		, int(vPos.x - width / 2.f)
		, int(vPos.y - height / 2.f)
		, (int)width, (int)height
		, pTex->GetDC()
		, 0, 0
		, (int)width, (int)height
		, bf);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetName(L"Missile_Player");
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f,-1.f));
	pMissile->SetDmg(5);

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER);

}


