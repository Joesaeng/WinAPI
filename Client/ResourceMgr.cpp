#include "pch.h"
#include "ResourceMgr.h"

#include "PathMgr.h"

#include "CCore.h"
#include "CTexture.h"

ResourceMgr::ResourceMgr()
	: m_mapTex{}
{}
ResourceMgr::~ResourceMgr()
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
	}
}

CTexture* ResourceMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}

	pTex = new CTexture;

	wstring strFilePath = PathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));

	return pTex;
}

CTexture* ResourceMgr::FindTexture(const wstring& _strKey)
{
	map<wstring, CTexture*>::iterator iter = m_mapTex.find(_strKey);
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}

	return iter->second;
}