#include "pch.h"
#include "PathMgr.h"

#include "CCore.h"

PathMgr::PathMgr()
	: m_szContentPath{}
{}

PathMgr::~PathMgr()
{}


void PathMgr::init()
{
	GetCurrentDirectory(255, m_szContentPath);// 현재 Directory 얻어옴

	// 상위 폴더로
	int iLen = (int)wcslen(m_szContentPath);
	// + bin\\content
	for (int i = iLen - 1; 0 <= i; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}

	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

	SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);
}

wstring PathMgr::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;

	size_t iAbsLen = wcslen(m_szContentPath);
	size_t iFullLen = strFilePath.length();

	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);

	return strRelativePath;
}
