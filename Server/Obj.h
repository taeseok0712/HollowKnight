#pragma once
#include "Enum.h"
#include "Global.h"

typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX; //x크기
	float fCY; //y크기
}INFO;

typedef struct tagFrame
{
	int iFrameStart; // 스프라이트 x 시작 지점. 
	int iFrameEnd; // 스프라이트 y축갯수 
	int iFrameScene; // 스프라이트 갯수 
	DWORD dwFrameSpeed;
	DWORD dwFrameTime; // 재생에 필요한 시간. 
}FRAME;

class CObj
{
public:
	CObj();
	virtual ~CObj();

public:
	// get
	// 충돌할때 필요할꺼야. 
	const INFO& Get_Info()const { return m_tInfo; }
	const RECT& Get_Rect()const { return m_tRect; }

public:
	//set
	void Set_Pos(float fx, float fy)
	{
		m_tInfo.fX = fx;
		m_tInfo.fY = fy;
	}
	// 충돌하면 죽일꺼야. 그래서 만듬. 
	void Set_Dead(bool bDead) { m_bIsDead = bDead; }
	void Set_Angle(float fAngle) { m_fAngle = fAngle; }
	void Set_Target(CObj* pTarget) { m_pTarget = pTarget; }
	void Set_Hp() { iHp -= 1; }
public:
	//기본함수 
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
