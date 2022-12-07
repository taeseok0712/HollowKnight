#pragma once
#include "Obj.h"
#include "Player.h"
#include "OtherPlayer.h"
#include <Windows.h>

class SubBoss :
	public CObj
{

public:
	enum STATE { STATE_ATT, STATE_IDLE, STATE_WALK };
	enum Direction { DR_LEFT, DR_RIGHT };
public:
	SubBoss();
	~SubBoss();

	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hdc) override;
	virtual void Release() override;
public:
	void FrameChange();
	void Set_Info(CObj* player);
	void Set_Info2(CObj* player);
	void findPlayer();
	void land();
	void Set_time(DWORD);

	MonsterData Get_Data();
public:
	BOOL hitOn;
	
	
private:
	CObj* m_pPlayer;
	CObj* m_pPlayer2;

	TCHAR* m_pFrameKey;
	STATE m_eCurState;
	STATE m_eNextState;



	Direction m_eDirc;
	Direction effectDir;
	POINT  m_tPosin;


	float m_fJumpPower; // �������� ���Ŀ��� v�� ���
	float m_fJumpAccel; // ���� ���ӵ�(t)��(��) ��� 

	RECT wall[22];

	BOOL a;
	RECT monsterSight; // ���� �þ߿���
	RECT monsterAttack; // ���� ���ݿ���
	RECT p; // �÷��̾��� ��Ʈ�ڽ� ����

	int moveDirect; // �̵����� ���� 1 -> ������ 0-> ����
	int moveCycle; // �̵����� ���� �ֱ�
	int attackDelay;
	int Collnum;
	RECT playerAttackBox;

	BOOL followOn;
	BOOL attackOn;
	BOOL parryingOn;
	BOOL IsColl;

	DWORD time;
};