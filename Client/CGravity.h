#pragma once

class CObject;

class CGravity
{
private:
	CObject* m_pOwner;		// Gravity�� �ۿ�ް� �ִ� ������Ʈ

	bool	m_bGround;		// ���� �پ��ִ��� ����

public:
	void finalupdate();

public:
	CGravity();
	~CGravity();

	friend class CObject;
};

