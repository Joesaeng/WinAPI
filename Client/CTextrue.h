#pragma once
#include "CRes.h"


class CTextrue :
    public CRes
{
private:
    HDC         m_dc;
    HBITMAP     m_hBit;

public:
    void Load(const wstring& _strFilePath);

public:
    CTextrue();
    ~CTextrue();
};

