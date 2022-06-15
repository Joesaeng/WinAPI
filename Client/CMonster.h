#pragma once
#include "CObject.h"
class CMonster :
    public CObject
{
private:
    Vec2        m_vCenterPos;
    float       m_fSpeed;
    float       m_fMaxDistance;
    int         m_iDir; // 1, -1
    


public:
    void SetSpeed(float _Speed) { m_fSpeed = _Speed; }
    float GetSpeed() { return m_fSpeed; }
    void SetMoveDistance(float _Distance) { m_fMaxDistance = _Distance; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
        
private:
    void MonsterFire();


public:
    virtual void update();

public:
    CMonster();
    ~CMonster();
};

