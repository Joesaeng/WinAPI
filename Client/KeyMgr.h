#pragma once


// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű �Է¿� ����, ������ �̺�Ʈ�� ��������.

// 2. Ű �Է� �̺�Ʈ ó��
// tap, hold, away

enum class KEY_STATE
{
	NONE, // ������ �ʾҰ�, �������� ������ ���� ����
	TAP, // �� ���� ����
	HOLD, // ������ �ִ�
	AWAY, // �� �� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,


	LAST,
}; // Ű�� �ο�

struct tKeyInfo
{
	KEY_STATE	eState; // Ű�� ���°�
	bool		bPrevPush;  // ���� �����ӿ����� Ű�� ���ȴ��� ����
};
class KeyMgr
{
	SINGLE(KeyMgr);

private:
	vector<tKeyInfo> m_vecKey;

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _ekey){return m_vecKey[(int)_ekey].eState;}
};

