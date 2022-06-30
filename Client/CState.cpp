#include "pch.h"
#include "CState.h"


CState::CState(MON_STATE _eState)
	: m_eState(_eState)
	, m_pAI(nullptr)
{
}

CState::~CState()
{
}
