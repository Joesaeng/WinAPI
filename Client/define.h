#pragma once

// ��ũ�δ� �Լ��� �ƴ� ġȯ�� ���̶�°��� �׻� ��������

// Singletone ��ũ��
#define SINGLE(type) public:static type* GetInst() { static type mgr; return &mgr; }\
						private: type(); ~type();

#define fDeltaTime CTimeMgr::GetInst()->GetfDT();
#define DeltaTime CTimeMgr::GetInst()->GetDT();