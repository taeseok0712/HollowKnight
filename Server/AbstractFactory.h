#pragma once
#include "Obj.h"
template<class T>
class CAbstractFactory
{
public:
	static CObj* Create()
	{
		CObj* pObj = new T;
		pObj->Initialize();
		return pObj;
	}

	static CObj* Create(float fx, float fy)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fx, fy);
		return pObj;
	}

	static CObj* Create(float fx, float fy, float fAngle)
	{
		CObj* pObj = new T;
		pObj->Initialize();
		pObj->Set_Pos(fx, fy);
		pObj->Set_Angle(fAngle);
		return pObj;
	}
};
