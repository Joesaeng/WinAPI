#include "pch.h"
#include "func.h"

#include "EventMgr.h"

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;

	EventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	EventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	EventMgr::GetInst()->AddEvent(evn);
}

void ChangeAIState(AI* _AI, MON_STATE _eNextState)
{
	tEvent evn = {};
	evn.eEvent = EVENT_TYPE::AI_STATE_CHANGE;
	evn.lParam = (DWORD_PTR)_AI;
	evn.wParam = (DWORD_PTR)_eNextState;

	EventMgr::GetInst()->AddEvent(evn);
}
