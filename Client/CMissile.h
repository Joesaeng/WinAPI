#pragma once
#include "CObject.h"



class CMissile :
    public CObject
{
private:
    float     m_iDir; // �� �Ʒ� ����

public:
    void SetDir(bool _bUp){if (_bUp) m_iDir = -1; else m_iDir = 1;}

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    CMissile();
    ~CMissile();
};

