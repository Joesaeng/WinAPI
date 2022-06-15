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

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	// Texture ·Îµù
	m_pTex = ResourceMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\player.bmp");
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
	
	SetPos(vPos);
}

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Width();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	/*BitBlt(_dc, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight, m_pTex->GetDC()
		, 0, 0, SRCCOPY);*/
	
	TransparentBlt(_dc
		, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;

	CMissile* pMissile = new CMissile;
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SetDir(Vec2(0.f,-1.f));

	CScene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	pCurScene->AddObject(pMissile, GROUP_TYPE::MISSILE);
}


