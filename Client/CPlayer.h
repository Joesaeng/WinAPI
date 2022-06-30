#pragma once
#include "CObject.h"


class CPlayer :
    public CObject
{
private:
    Vec2    m_dir;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();

    CLONE(CPlayer)
public:
    CPlayer();
    ~CPlayer();
};

