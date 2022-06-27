#pragma once
#include "CUI.h"
class CBtnUI :
    public CUI
{
private:

public:
    virtual void MouseLBtnDown();
    virtual void MouseLBtnUp();
    virtual void MouseLBtnClicked();

    CLONE(CBtnUI);
public:
    CBtnUI();
    ~CBtnUI();

};

