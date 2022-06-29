#pragma once
#include "CUI.h"
#include "pch.h"

class CTitleUI :
    public CUI
{
private:
    Vec2    m_vDragStart;

public:
    virtual void update();
    virtual void render(HDC _dc);


    virtual void MouseOn();
    virtual void MouseLBtnDown();
    virtual void MouseLBtnUp();
    virtual void MouseLBtnClicked();

    CLONE(CTitleUI);
public:
    CTitleUI();
    ~CTitleUI();
};

