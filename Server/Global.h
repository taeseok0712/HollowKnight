#define WINCX 1600
#define WINCY 900

#define OBJ_DEAD 1
#define OBJ_NOEVENT 0

#define PI 3.141592f
#define GRAVITY 9.8f
#define DegreeToRadian(x) x * PI / 180.f
#define RadianToDegree(x) x * 180.f/ PI

#define NULL_CHECK(ptr) assert(!(ptr))

#define TILECX 64
#define TILECY 64

#define TILEX 100
#define TILEY 100


#define DECLARE_SINGLETON(ClassName)		\
public:										\
	static ClassName* Get_Instance()		\
	{										\
		if (nullptr == m_pInstance)			\
			m_pInstance = new ClassName;	\
											\
		return m_pInstance;					\
	}										\
	static void Destroy_Instance()			\
	{										\
		if (m_pInstance)					\
		{									\
			delete m_pInstance;				\
			m_pInstance = nullptr;			\
		}									\
	}										\
private:									\
	static ClassName* m_pInstance;


#define IMPLEMENT_SINGLETON(ClassName)			\
ClassName* ClassName::m_pInstance = nullptr;	

#define D_CAST(className, Obj) dynamic_cast<className*>(Obj)

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <windows.h>
#include <string>

using namespace std;