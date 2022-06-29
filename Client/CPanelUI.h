#pragma once
#include "CUI.h"
#include "pch.h"


class CPanelUI :
    public CUI
{
private:
    Vec2    m_vDragStart;


public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    void CreateTileUI();

    virtual void MouseOn();
    virtual void MouseLBtnDown();
    virtual void MouseLBtnUp();
    virtual void MouseLBtnClicked();

    CLONE(CPanelUI);
public:
    CPanelUI();
    ~CPanelUI();
};

