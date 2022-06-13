#pragma once

// ��ũ�δ� �Լ��� �ƴ� ġȯ�� ���̶�°��� �׻� ��������

// Singletone ��ũ��
#define SINGLE(type) public:static type* GetInst() { static type mgr; return &mgr; }\
						private: type(); ~type();

#define fDeltaTime TimeMgr::GetInst()->GetfDT() // ��ŸŸ��
#define DeltaTime TimeMgr::GetInst()->GetDT()

#define MgrINIT GetInst()->init() // �Ŵ��� �ʱ�ȭ
#define MgrUPDATE GetInst()->update() // �Ŵ��� ������Ʈ

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