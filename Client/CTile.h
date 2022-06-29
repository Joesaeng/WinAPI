#pragma once
#include "CObject.h"

class CTexture;

class CTile :
    public CObject
{
private:
    CTexture*   m_pTileTex;
    int         m_iImageIdx;

public:
    void SetTexture(CTexture* _pTex)
    {
        m_pTileTex = _pTex;
    }

    void AddImgIdx() { ++m_iImageIdx; }
    void SetImgIdx(int _index) { m_iImageIdx = _index; }
private:

    virtual void update();
    virtual void render(HDC _dc);

public:
    virtual void Save(FILE* _pFile);
    virtual void Load(FILE* _pFile);

    CLONE(CTile);
public:
    CTile();
    ~CTile();

};

