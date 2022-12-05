#pragma once
#include "framework.h"
class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	// get
	// �浹�Ҷ� �ʿ��Ҳ���. 
	const INFO& Get_Info()const { return m_tInfo; }
	const RECT& Get_Rect()const { return m_tRect; }

public:
	//set
	void Set_Pos(float fx, float fy)
	{
		m_tInfo.fX = fx;
		m_tInfo.fY = fy;
	}
	// �浹�ϸ� ���ϲ���. �׷��� ����. 
	void Set_Dead(bool bDead) { m_bIsDead = bDead; }
	void Set_Angle(float fAngle) { m_fAngle = fAngle; }
	void Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	void Set_Hp() { iHp -= 1; }
public:
	//�⺻�Լ� 
	virtual void Initialize() = 0;
	virtual int Update() = 0;
	virtual void LateUpdate() = 0;
	virtual void Render(HDC hDC) = 0;
	virtual void Release() = 0;
	
public:
	void UpdateRect();
	void FrameMove();
	RECT HitBox;
	bool Check_Collision(CObj* Player, CObj* monster);
	bool CanHit;
	int iHp;
	bool effectOn;
	RECT drawEffect;
	void setDead(bool in);
	bool getIsDead();

	void setData(MonsterData dt);
	
protected:
	INFO m_tInfo;
	RECT m_tRect;
	FRAME m_tFrame;
	
	float m_fSpeed;
	bool m_bIsDead;
	float m_fAngle;
	CObj* m_pTarget;
	bool m_bIsInit;


};
