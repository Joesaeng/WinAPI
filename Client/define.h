#pragma once

// ��ũ�δ� �Լ��� �ƴ� ġȯ�� ���̶�°��� �׻� ��������

// Singletone ��ũ��
#define SINGLE(type) public:static type* GetInst() { static type mgr; return &mgr; }
