#include "pch.h"
#include "CScene_Start.h"

#include "PathMgr.h"
#include "CollisionMgr.h"
#include "TimeMgr.h"

#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CTexture.h"
#include "CRigidBody.h"

#include "SceneMgr.h"
#include "KeyMgr.h"
#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "SelectGDI.h"

CScene_Start::CScene_Start()
	:m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{
	if (KEY_HOLD(KEY::LBTN))
	{
		CreateForce();
		m_bUseForce = true;
	}
	else
	{
		m_bUseForce = false;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);
		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->IsDead()) // ������Ʈ�� isDead ���� üũ
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					if (fLen < m_fForceRadius)
					{
						float fRatio = 1.f - (fLen / m_fForceRadius);
						float fForce = m_fForce* fRatio;

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
					}
				}
				vecObj[j]->update();
			}
		}
	}
	
	
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}
}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	if (m_bUseForce)
	{
		SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
		SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

		m_fCurRadius += m_fForceRadius * 3.f * fDeltaTime;
		if (m_fCurRadius > m_fForceRadius)
			m_fCurRadius = 0.f;
		Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

		Ellipse(_dc
			, (int)(vRenderPos.x - m_fCurRadius)
			, (int)(vRenderPos.y - m_fCurRadius)
			, (int)(vRenderPos.x + m_fCurRadius)
			, (int)(vRenderPos.y + m_fCurRadius));
	}
	

}

void CScene_Start::Enter()
{
	// Player Object �߰�
	CObject* pObj = new CPlayer;
	pObj->SetPos(Vec2(640.f,584.f));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CCamera::GetInst()->SetTarget(pObj);

	Vec2 vResolution = CCore::GetInst()->GetResolution();

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(580.f, 584.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);

	// ���� ��ġ
	
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(640.f, 100.f));
	
	AddObject(pMon, GROUP_TYPE::MONSTER);

	// Ÿ�� �ε�
	//LoadTile(L"tile\\StartTile.tile");


	// �浹 ����
	// Player �׷�� Monster �׸� ���� �浹üũ
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	// Camera Look ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	// Camera ȿ�� ����
	CCamera::GetInst()->CamEffect(CAM_EFFECT::FADE_OUT, 1.f);
	CCamera::GetInst()->CamEffect(CAM_EFFECT::FADE_IN, 1.f);

	// �߷� ����
	SetGravity(500.f);
}

void CScene_Start::Exit()
{
	DeleteAll();

	CollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);


}
