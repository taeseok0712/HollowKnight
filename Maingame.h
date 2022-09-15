#pragma once
#include "framework.h"

class CObj;
class CMainGame
{
public:
	CMainGame();
	~CMainGame();
public:
	void Initialize();
	void Update();
	void LateUpdate();
	void Render();
	void Release();

private:
	SCENEID m_eScene;
	HDC m_hDC;
	CObj* m_pPlayer;
	CObj* m_pHush;
};
