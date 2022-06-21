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
    UINT        m_iHP;


public:
    void SetSpeed(float _Speed) { m_fSpeed = _Speed; }
    float GetSpeed() { return m_fSpeed; }
    void SetMoveDistance(float _Distance) { m_fMaxDistance = _Distance; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }
    Vec2 GetCenterPos() { return m_vCenterPos; }

private:
    void MonsterFire();
    void isHit(CObject* _pHit);

public:
    virtual void OnCollisionEnter(CCollider* _pOther);


public:
    virtual void update();

    CLONE(CMonster)

public:
    CMonster();
    ~CMonster();
};

