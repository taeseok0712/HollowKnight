#pragma once

#include "Scene.h"
#include <Windows.h>
#include "Player.h"
class CStage2:public CScene
{
public:
	CStage2();
	~CStage2();

	// CScene��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
private:
	CObj* m_pPlayer;
	int PlayerHp;
};

