#pragma once

// 매크로는 함수가 아닌 치환된 것이라는것을 항상 인지하자

// Singletone 매크로
#define SINGLE(type) public:static type* GetInst() { static type mgr; return &mgr; }\
						private: type(); ~type();

#define fDeltaTime TimeMgr::GetInst()->GetfDT() // 델타타임(float)
#define DeltaTime TimeMgr::GetInst()->GetDT()   // 델타타임(double)

#define MgrINIT GetInst()->init() // 매니저 초기화
#define MgrUPDATE GetInst()->update() // 매니저 업데이트

#define KEY_CHECK(key, state) KeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key, KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key, KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key, KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key, KEY_STATE::NONE)

#define PI 3.1415926535f

enum class GROUP_TYPE
{
	DEFAULT,
	PLAYER,
	MISSILE,
	MONSTER,


	END = 32
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};