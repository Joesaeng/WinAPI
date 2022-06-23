#include "pch.h"
#include "CAnimation.h"

#include "TimeMgr.h"

#include "CTexture.h"
#include "CObject.h"
#include "CAnimator.h"
#include "CCamera.h"

CAnimation::CAnimation()
	: m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrame(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDeltaTime;

	if (m_fAccTime > m_vecFrame[m_iCurFrame].fDuration)
	{
		++m_iCurFrame;

		if (m_vecFrame.size() <= m_iCurFrame)
		{
			m_iCurFrame = -1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}
		m_fAccTime = m_fAccTime - m_vecFrame[m_iCurFrame].fDuration;

	}
}

void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;

	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	vPos += m_vecFrame[m_iCurFrame].vOffset; // Object Position에 Offset 만큼 추가 이동위치
	
	// 렌더링 좌표로 변환
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	TransparentBlt(_dc
		, (int)(vPos.x - m_vecFrame[m_iCurFrame].vSlice.x / 2.f)
		, (int)(vPos.y - m_vecFrame[m_iCurFrame].vSlice.y / 2.f)
		, (int)(m_vecFrame[m_iCurFrame].vSlice.x)
		, (int)(m_vecFrame[m_iCurFrame].vSlice.y)
		, m_pTex->GetDC()
		, (int)(m_vecFrame[m_iCurFrame].vLeftTop.x)
		, (int)(m_vecFrame[m_iCurFrame].vLeftTop.y)
		, (int)(m_vecFrame[m_iCurFrame].vSlice.x)
		, (int)(m_vecFrame[m_iCurFrame].vSlice.y)
		, RGB(255, 0, 255));
}

void CAnimation::Create(CTexture* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep, float _fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;

	tAnimFrame frame = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frame.fDuration = _fDuration;
		frame.vSlice = _vSliceSize;
		frame.vLeftTop = _vLeftTop + (_vStep * i);

		m_vecFrame.push_back(frame);
	}
}


