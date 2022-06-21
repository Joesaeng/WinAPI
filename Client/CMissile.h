#pragma once
#include "CObject.h"
class CCollider;

class CMissile :
    public CObject
{
private:
    float     m_fTheta; // 이동 방향

    Vec2      m_vDir;
    float      m_deadCount;
    UINT      m_iDmg;


public:
    void SetDir(float _fTheta) { m_fTheta = _fTheta; }
    void SetDir(Vec2 _vDir) 
    { 
        m_vDir = _vDir;
        m_vDir.Normalize();
    }
    void SetDmg(UINT _dmg) { m_iDmg = _dmg; }
    UINT GetDmg() { return m_iDmg; }


public:
    virtual void update();
    virtual void render(HDC _dc);
    // 이동(방향 *속도)
    virtual void OnCollisionEnter(CCollider* _pOther);

public:
    CMissile();
    ~CMissile();
};

