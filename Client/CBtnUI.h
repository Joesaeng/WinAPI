#pragma once
#include "CUI.h"
#include "CScene.h"
#include "CObject.h"

typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);

typedef void(CScene::*SCENE_MEMFUNC)(void);

typedef void(CObject::*OBJECT_MEMFUNC)(void);

class CTexture;

class CBtnUI :
    public CUI
{
private:
    BTN_FUNC        m_pFunc;
    DWORD_PTR       m_param1;
    DWORD_PTR       m_param2;

    SCENE_MEMFUNC   m_pSceneFunc;
    CScene*         m_pSceneInst;
    

public:
    

    virtual void render(HDC _dc);
    
    virtual void MouseOn();
    virtual void MouseLBtnDown();
    virtual void MouseLBtnUp();
    virtual void MouseLBtnClicked();

    void SetClikedCallBack(BTN_FUNC _pFunc, DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;

    }
    void SetClikedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
    {
        m_pSceneInst = _pScene;
        m_pSceneFunc = _pSceneFunc;
    }
   
 
    CLONE(CBtnUI);
public:
    CBtnUI();
    virtual ~CBtnUI();

};

