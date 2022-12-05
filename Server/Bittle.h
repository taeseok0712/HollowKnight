#pragma once
#pragma once
#include "Obj.h"
#include "Player.h"
#include <Windows.h>

using namespace std;


class Bittle :
	public CObj
{

public:
	enum STATE { STATE_ATT, STATE_IDLE, STATE_WALK };
	enum Direction { DR_LEFT, DR_RIGHT };
public:
	Bittle();
	~Bittle();
	Bittle(float x, float y);
	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
public:
	void FrameChange();
	void Set_Info(CObj* player);
	void findPlayer();
	void land();
	void Set_time(DWORD Hittime);
public:
	BOOL hitOn;
private:

	CObj* m_pPlayer;

	TCHAR* m_pFrameKey;
	STATE m_eCurState;
	STATE m_eNextState;
	Direction m_eDirc;
	POINT  m_tPosin;

	float m_fJumpPower; // 자유낙하 공식에서 v를 담당
	float m_fJumpAccel; // 점프 가속도(t)을(를) 담당 
	RECT wall[22];


	DWORD time;
	RECT monsterSight; // 몬스터 시야영dur
	RECT p; // 플레이어의 히트박스 정보

	int moveDirect; // 이동방향 상태 1 -> 오른쪽 0-> 왼쪽
	int moveCycle; // 이동방향 변경 주기
	int attackDelay;
	int Collnum;

	BOOL followOn;
	BOOL attackOn;
	BOOL IsColl;
};