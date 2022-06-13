#pragma once

class CScene;

class SceneMgr
{
	SINGLE(SceneMgr);
private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];  // ��� �� ���
	CScene*		m_pCurScene;						// ���� ��

public:
	void init();
	void update();
	void render(HDC _dc);
};
