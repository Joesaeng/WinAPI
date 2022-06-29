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
	// 1. FocusedUI Ȯ��
	m_pFocuseUI = GetFocusedUI();

	if (!m_pFocuseUI)
		return;

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// 2. FocusedUI ������ ,�θ� UI ����, �ڽ� UI �� �� ���� Ÿ���� �� UI�� �����´�.
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
			// ���ʹ�ư ���� ���ȴ� üũ�� �ٽ� �����Ѵ�
			pTargetUI->m_bLbtnDown = false;
		}
	}
}

void UIMgr::SetFocusedUI(CUI* _pUI)
{
	// �̹� ��Ŀ�� ���� ��� or ��Ŀ�� ������û�� ���
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

	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(iter);
	vecUI.push_back(m_pFocuseUI);
}

CUI* UIMgr::GetFocusedUI()
{
	CScene* pCurScene = SceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// ���� ��Ŀ�� UI�� �޾Ƶΰ� ������ �Ͼ�� ������ �״�� ��ȯ�Ѵ�
	CUI* pFocusedUI = m_pFocuseUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// ���콺 ���ʹ�ư TAP �� �߻��ߴٴ� ����
	vector<CObject*>::iterator targetiter = vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();
	for (; iter < vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targetiter = iter;
		}
	}

	// �̹��� Focus �� UI �� ����.
	if (vecUI.end() == targetiter)
		return nullptr;

	pFocusedUI = (CUI*)*targetiter;

	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(targetiter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* UIMgr::GetTargetUI(CUI* _pParentUI) // �θ� UI ������ ������ Ÿ���� �� UI�� ã�Ƽ� ��ȯ�Ѵ�.
{
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	CUI* pTargetUI = nullptr;
	// 1. �θ� UI ����, ��� �ڽĵ��� �˻� �Ѵ�.
	static list<CUI*> queue; // list �� queue ó�� ����� ��.
	static vector<CUI*> vecNontarget;

	queue.clear();
	vecNontarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI �� TargetUI ���� Ȯ��
		// Ÿ�� UI �� ��, �� �켱������ ���� ������ ������ ������ �ڽ� UI
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


