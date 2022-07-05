#pragma once
#include "CObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    ATTACK,
    HIT,
    DEAD,
    JUMP,
    FALL,
};

enum class PLAYER_ATTACK_STATE
{
    NORMAL_ATTACK_1,
    NORMAL_ATTACK_2,
    NORMAL_ATTACK_3,
    SKILL_ATTACK_1,

};

class CTexture;

class CPlayer :
    public CObject
{
private:
    Vec2            m_dir;
    float           m_moveSpeed;

    int             m_iDir;
    int             m_ipDir;

    PLAYER_STATE    m_eCurState;
    PLAYER_STATE    m_ePrevState;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();
    void update_state();
    void update_animation();
    void MovePlayer();

    CLONE(CPlayer)
public:
    CPlayer();
    ~CPlayer();
};

