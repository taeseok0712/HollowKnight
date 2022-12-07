#pragma once
#include "Obj.h"
class HushKnight :public CObj
{
public:
	enum STATE { STATE_ATT, STATE_IDLE, STATE_WALK };
	enum Direction { DR_LEFT, DR_RIGHT };
public:
	HushKnight();
	~HushKnight();
	HushKnight(float x, float y);
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

	MonsterData Get_Data();

	//�����̿�
	void Set_time(DWORD Hittime);
public:
	BOOL hitOn;


private:
	CObj* m_pPlayer;
	CObj* m_pPlayer2;
	TCHAR* m_pFrameKey;
	STATE m_eCurState;
	STATE m_eNextState;
	Direction m_eDirc;
	POINT  m_tPosin;
	float m_fDistance;
	float m_fJumpPower; // �������� ���Ŀ��� v�� ���
	float m_fJumpAccel; // ���� ���ӵ�(t)��(��) ��� 
	RECT wall[22];

	DWORD time;
	RECT monsterSight; // ���� �þ߿���
	RECT monsterAttack; // ���� ���ݿ���
	RECT p; // �÷��̾��� ��Ʈ�ڽ� ����

	int moveDirect; // �̵����� ���� 1 -> ������ 0-> ����
	int moveCycle; // �̵����� ���� �ֱ�
	int attackDelay;
	int Collnum;

	BOOL followOn;
	BOOL attackOn;
	BOOL IsColl;

};
