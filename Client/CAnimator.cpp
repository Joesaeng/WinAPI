#include "pch.h"
#include "CAnimator.h"

#include "CObject.h"
#include "CAnimation.h"

CAnimator::CAnimator()
	: m_pOwner(nullptr)
	, m_mapAnim{}
{
}

CAnimator::~CAnimator()
{
	Safe_Delete_Map(m_mapAnim);
}

void CAnimator::CreateAnimation()
{
}

void CAnimator::FindAnimation()
{
}

void CAnimator::Play()
{
}


