#pragma once
#include "CObject.h"


class CPlayer :
    public CObject
{
private:
    Vec2    m_dir;
    float   m_moveSpeed;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();
    void MovePlayer();

    CLONE(CPlayer)
public:
    CPlayer();
    ~CPlayer();
};

