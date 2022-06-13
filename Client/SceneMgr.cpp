#include "pch.h"
#include "SceneMgr.h"
#include "CScene_Start.h"

SceneMgr::SceneMgr()
	: m_arrScene{}
	,m_pCurScene(nullptr)
{
	
}


SceneMgr::~SceneMgr()
{
	// �� ���� ����
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if(nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void SceneMgr::init()
{
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");

	//m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage_01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage_02;

	// ���� �� ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

void SceneMgr::update()
{
	m_pCurScene->update();
}

void SceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}