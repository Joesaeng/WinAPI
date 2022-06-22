#pragma once

class CAnimator;
class CTexture;

struct tAnimFrame
{
	Vec2	vLeftTop;
	Vec2	vSlice;
	Vec2	vOffset;
	float	fDuration;
};

class CAnimation
{
private:
	wstring				m_strName;
	CAnimator*			m_pAnimator;
	CTexture*			m_pTex;		 // Animation 이 사용하는 Texture
	vector<tAnimFrame>	m_vecFrame;  // 모든 프레임 정보
	int					m_iCurFrame; // 현재 프레임
	float				m_fAccTime;	 // 시간 누적

	bool				m_bFinish;	 // 애니메이션이 끝남
public:

	const wstring& GetName() { return m_strName; }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx) { m_bFinish = false; m_iCurFrame = _iFrameIdx; m_fAccTime = 0.f; }
	tAnimFrame& GetFrame(size_t _iIdx) { return m_vecFrame[_iIdx]; }
	size_t GetMaxFrame() { return m_vecFrame.size(); }
private:
	void SetName(const wstring& _strName) { m_strName = _strName; }

public:
	void update();
	void render(HDC _dc);

	void Create(CTexture* _pTex, Vec2 _vLeftTop, Vec2 _vSliceSize, Vec2 _vStep,float _fDuration ,UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

