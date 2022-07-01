#include "pch.h"
#include "EventMgr.h"

#include "CObject.h"
#include "SceneMgr.h"
#include "CScene.h"

#include "AI.h"
#include "CState.h"

#include "UIMgr.h"

EventMgr::EventMgr()
{

}
EventMgr::~EventMgr()
{

}

void EventMgr::update()
{
	// ===============================================
	// 이전 프레임에 Dead로 등록해둔 오브젝트들을 삭제한다
	// ===============================================

	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();
	// ==========
	// Event 처리
	// ==========

	for (size_t i = 0; i < m_vecEvent.size(); ++i)
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}

void EventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEvent)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Adress
		// wParam : Group Type
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;

		SceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Adress
		// Object 를 Dead 상태로 변경
		// 삭제예정 오브젝트들을 모아둔다.
		CObject* pDeadObj = (CObject*)_eve.lParam;
		if (pDeadObj->IsDead())
			return;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam : Next Scene Type
		SceneMgr::GetInst()->ChangeScene((SCENE_TYPE)_eve.lParam);

		// 포커스 UI 해제
		UIMgr::GetInst()->SetFocusedUI(nullptr);
	}
	case EVENT_TYPE::AI_STATE_CHANGE:
	{
		// lParam : AI 포인터 
		AI* pAI = (AI*)_eve.lParam;
		// wParam : Next State
		MON_STATE eNextState = (MON_STATE)_eve.wParam;
		pAI->ChangeState(eNextState);
	}
		break;
	}
}
