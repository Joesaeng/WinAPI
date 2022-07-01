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
	// ���� �����ӿ� Dead�� ����ص� ������Ʈ���� �����Ѵ�
	// ===============================================

	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();
	// ==========
	// Event ó��
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
		// Object �� Dead ���·� ����
		// �������� ������Ʈ���� ��Ƶд�.
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

		// ��Ŀ�� UI ����
		UIMgr::GetInst()->SetFocusedUI(nullptr);
	}
	case EVENT_TYPE::AI_STATE_CHANGE:
	{
		// lParam : AI ������ 
		AI* pAI = (AI*)_eve.lParam;
		// wParam : Next State
		MON_STATE eNextState = (MON_STATE)_eve.wParam;
		pAI->ChangeState(eNextState);
	}
		break;
	}
}
