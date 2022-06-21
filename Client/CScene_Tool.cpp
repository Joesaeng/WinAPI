#include "pch.h"
#include "CScene_Tool.h"

#include "CScene.h"
#include "KeyMgr.h"


CScene_Tool::CScene_Tool()
{
}

CScene_Tool::~CScene_Tool()
{
}



void CScene_Tool::update()
{
	CScene::update();
	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::START);
	}
}

void CScene_Tool::Enter()
{
}

void CScene_Tool::Exit()
{
}

