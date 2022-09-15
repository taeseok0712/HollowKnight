#pragma once
#include "Scene.h"
#include <Windows.h>
#include "Player.h"
class CStage1:public CScene
{
public:
	CStage1();
	~CStage1();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	bool Wave2clear;
	CObj* m_pPlayer;
	int PlayerHp;
	CObj* m_pHush;
	CObj* m_pFly;
	CObj* m_pBug;
	CObj* m_pSub;
	CObj* m_pbittle;
	CObj* m_pbittle2;
	CObj* m_pbittle3;
	CObj* m_pbittle4;
	CObj* m_pHushKni;
	int wave;
};

