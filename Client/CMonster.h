#pragma once
#include "CObject.h"

class AI;

class CMonster :
    public CObject
{
private:
    float       m_fSpeed;
    UINT        m_iHP;

    AI*         m_AI;

public:
    void SetSpeed(float _Speed) { m_fSpeed = _Speed; }
    float GetSpeed() { return m_fSpeed; }

    void SetAI(AI* _pAI) { m_AI = _pAI; }

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

