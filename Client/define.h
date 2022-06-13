#pragma once

// 매크로는 함수가 아닌 치환된 것이라는것을 항상 인지하자

// Singletone 매크로
#define SINGLE(type) public:static type* GetInst() { static type mgr; return &mgr; }\
						private: type(); ~type();

#define fDeltaTime CTimeMgr::GetInst()->GetfDT();
#define DeltaTime CTimeMgr::GetInst()->GetDT();