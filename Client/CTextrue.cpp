#include "pch.h"
#include "CTextrue.h"

CTextrue::CTextrue()
	: m_hBit(0)
	, m_dc(0)
{
}

CTextrue::~CTextrue()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTextrue::Load(const wstring& _strFilePath)
{
	m_hBit = (HBITMAP)LoadImage(nullptr, _strFilePath.c_str(),IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);

	assert(m_hBit);
}
