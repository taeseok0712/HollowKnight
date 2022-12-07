#pragma once
#include "Obj.h"
class CMyButton :
	public CObj
{
public:
	CMyButton();
	virtual ~CMyButton();
public:
	void Set_FrameKey(TCHAR* pKey) { m_pFrameKey = pKey; }
public:

	// CObj을(를) 통해 상속됨
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;

private:
	TCHAR* m_pFrameKey;
	int m_iDrawID;
};

