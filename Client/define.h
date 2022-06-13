#pragma once

// 매크로는 함수가 아닌 치환된 것이라는것을 항상 인지하자

// Singletone 매크로
#define SINGLE(type) public:static type* GetInst() { static type mgr; return &mgr; }\
						private: type(); ~type();

#define fDeltaTime TimeMgr::GetInst()->GetfDT() // 델타타임
#define DeltaTime TimeMgr::GetInst()->GetDT()

#define MgrINIT GetInst()->init() // 매니저 초기화
#define MgrUPDATE GetInst()->update() // 매니저 업데이트

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