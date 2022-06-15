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
	GetCurrentDirectory(255, m_szContentPath);// ���� Directory ����

	// ���� ������
	int iLen = wcslen(m_szContentPath);
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
