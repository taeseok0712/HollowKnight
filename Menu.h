#pragma once
#include "Scene.h"

#include "framework.h"
class CMenu :public CScene
{
public:
	CMenu();
	~CMenu();

	// CScene을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	POINT m_Pmouse;
	RECT m_RStart;
	RECT m_RExit;
	int m_iTochange;
	int m_iTochange2;
};

