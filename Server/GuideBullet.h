#pragma once
#include "Obj.h"
class CGuideBullet :
	public CObj
{
public:
	CGuideBullet();
	virtual ~CGuideBullet();
public:
	// CObj��(��) ���� ��ӵ�
	virtual void Initialize() override;
	virtual int Update() override;
	virtual void LateUpdate() override;
	virtual void Render(HDC hDC) override;
	virtual void Release() override;
};

