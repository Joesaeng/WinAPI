#include "pch.h"
#include "UIMgr.h"

#include "SceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "KeyMgr.h"

UIMgr::UIMgr()
	: m_pFocuseUI(nullptr)
{

}
UIMgr::~UIMgr()
{

}
void UIMgr::update()
{
	// 1. FocusedUI 확인
	m_pFocuseUI = GetFocusedUI();

	if (!m_pFocuseUI)
		return;

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 2. FocusedUI 내에서 ,부모 UI 포함, 자식 UI 들 중 실제 타겟팅 된 UI를 가져온다.
	CUI* pTargetUI = GetTargetUI(m_pFocuseUI);

	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLBtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLBtnUp();

			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLBtnClicked();
			}
			// 왼쪽버튼 떼면 눌렸던 체크를 다시 해제한다
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void UIMgr::SetFocusedUI(CUI* _pUI)
{
	// 이미 포커싱 중인 경우 or 포커싱 해제요청인 경우
	if (m_pFocuseUI == _pUI || nullptr == _pUI)
	{
		m_pFocuseUI = _pUI;
		return;
	}

	m_pFocuseUI = _pUI;
	CScene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter < vecUI.end(); ++iter)
	{
		if (m_pFocuseUI == *iter)
		{
			break;
		}
	}

	// 벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(iter);
	vecUI.push_back(m_pFocuseUI);
}

CUI* UIMgr::GetFocusedUI()
{
	CScene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 UI를 받아두고 변경이 일어나지 않으면 그대로 반환한다
	CUI* pFocusedUI = m_pFocuseUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// 마우스 왼쪽버튼 TAP 이 발생했다는 전제
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter < vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// 이번에 Focus 된 UI 가 없다.
	if (vecUI.end() == targetiter)
		return nullptr;

	pFocusedUI = (CUI*)*targetiter;

	// 벡터 내에서 맨 뒤로 순번 교체
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* UIMgr::GetTargetUI(CUI* _pParentUI) // 부모 UI 내에서 실제로 타겟팅 된 UI를 찾아서 반환한다.
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CUI* pTargetUI = nullptr;
	// 1. 부모 UI 포함, 모든 자식들을 검사 한다.
	static list<CUI*> queue; // list 를 queue 처럼 사용할 것.
	static vector<CUI*> vecNontarget;

	queue.clear();
	vecNontarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI = queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI 가 TargetUI 인지 확인
		// 타겟 UI 들 중, 더 우선순위가 높은 기준은 더낮은 계층의 자식 UI
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNontarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNontarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNontarget.size(); ++i)
		{
			vecNontarget[i]->m_bLbtnDown = false;
		}
	}
	
	return pTargetUI;
}


