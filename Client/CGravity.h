#pragma once

class CObject;

class CGravity
{
private:
	CObject* m_pOwner;		// Gravity를 작용받고 있는 오브젝트

	bool	m_bGround;		// 땅에 붙어있는지 여부

public:
	void finalupdate();

public:
	CGravity();
	~CGravity();

	friend class CObject;
};

