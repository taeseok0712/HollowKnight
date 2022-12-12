#pragma once
#include "Obj.h"

#include <Windows.h>

class Player :
	public CObj
{
public:
	enum STATE { STATE_ATT, STATE_IDLE, STATE_WALK, STATE_HIT, STATE_JUMP, STATE_FALL, STATE_LAND, STATE_DEAD,STATE_ATTD,STATE_ATTU };

public:
	Player();
	~Player();

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override { CObj::UpdateRect(); };
	virtual void Release() override;
public:
	void IsJumping();
	void IsOffset();
	void FrameChange();
	bool CheckCollE2M(CObj* monster);
	void SoundON();
	int GetHp();
	void Set_InfoHusk(CObj* Monster);
	void Set_InfoFly(CObj* Monster);
	void Set_InfoBug(CObj* Monster);
	void Set_InfoSubBoss(CObj* Monster);
	void Set_Infobit(CObj* Monster);
	void Set_Infobit2(CObj* Monster);
	void Set_Infobit3(CObj* Monster);
	void Set_Infobit4(CObj* Monster);
	void Set_InfoHushK(CObj* Monster);
	void Set_Wave(int wave) { m_wave = wave; };

	void Set_PlayerData(PlayerData playerdata);
	PlayerData Get_PlayerData();

	bool getStage();
	RECT Attack_box; // 어택박스
	bool Attck_ON;
private:
	TCHAR* m_pFrameKey;
	TCHAR* Attck;
	UpDown UDS;
	bool b_IsChange;
	bool b_canChange;
	bool IsHit;
	DWORD Hittime;
	RECT rcTemp;
	bool Attacked;
	int m_wave;
	int Hp;
	bool m_bIsJump;
	bool IsColl;
	float Scrollspeed_Y;
	float Scrollspeed_X = 10.f;
	int Collnum;
	float m_fJumpPower; // 자유낙하 공식에서 v를 담당
	float m_fJumpAccel; // 점프 가속도(t)을(를) 담당 
	bool IsFall;
	STATE m_eCurState;
	STATE m_eNextState;
	bool isLand;
	POINT  m_tPosin;
	float m_fDistance;
	Direction m_eDirc;
	RECT wall[22];
	bool deadswitch;
	bool Sound_On;
	DWORD deadtime;
	float FSpeed;
private:
	CObj* pHusk;
	CObj* pFly;
	CObj* pBug;
	CObj* pSubBoss;
	CObj* pbittle;
	CObj* pbittle2;
	CObj* pbittle3;
	CObj* pbittle4;
	CObj* pHushK;
};