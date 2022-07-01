#pragma once
#include "CObject.h"

struct tMonInfo
{
    float       fSpeed;         // 속도
    float       fHP;            // 체력
    float       fRecogRange;    // 인지 범위
    float       fAtkRange;      // 공격 범위
    float       fDamage;           // 공격력
};


class AI;

class CMonster :
    public CObject
{
private:
    
    AI*         m_AI;
    tMonInfo    m_tInfo;

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    float GetHP() { return m_tInfo.fHP; }
    const tMonInfo& GetMonsterInfo() { return m_tInfo; }

    void SetAI(AI* _pAI);

private:
    void MonsterFire();
    void isHit(CObject* _pHit);

    void SetMonInfo(const tMonInfo& _info){m_tInfo = _info;}

public:
    virtual void OnCollisionEnter(CCollider* _pOther);


public:
    virtual void update();

    CLONE(CMonster)

public:
    CMonster();
    ~CMonster();

    friend class CMonFactory;
};

