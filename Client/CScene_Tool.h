#pragma once
#include "CScene.h"

class CUI;

class CScene_Tool :
    public CScene
{
private:
    CUI*    m_pUI;
    UINT    m_index;

public:
    virtual void update();
    virtual void Enter();
    virtual void Exit();

public:
    void SetTileNum(UINT _index) { m_index = _index; }
    void SetTileIdx();

    void SetAllTile();
    void SaveTileData();
    void SaveTile(const wstring& _strFilePath);

    void LoadTileData();

public:
    CScene_Tool();
    ~CScene_Tool();

};

