#pragma once

class CScene;

class SceneMgr
{
	SINGLE(SceneMgr);
private:
	CScene*		m_arrScene[(UINT)SCENE_TYPE::END];  // ¸ðµç ¾À ¸ñ·Ï
	CScene*		m_pCurScene;						// ÇöÀç ¾À

public:
	void init();
	void update();
	void render(HDC _dc);

public:
	CScene* GetCurScene() { return m_pCurScene; }
};

