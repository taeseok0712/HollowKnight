#pragma once
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
typedef struct tagLinePos
{
	tagLinePos()
	{
		ZeroMemory(this, sizeof(tagLinePos));
	}
	tagLinePos(float x, float y)
		:fX(x)
		, fY(y)
	{

	}
	float fX;
	float fY;
}LINEPOS;
typedef struct tagLine
{
	tagLine()
	{
		ZeroMemory(this, sizeof(tagLine));
	}
	tagLine(LINEPOS& tLeft, LINEPOS& tRight)
		:tLPoint(tLeft)
		, tRPoint(tRight)
	{}
	LINEPOS tLPoint;
	LINEPOS tRPoint;
}LINEINFO;

class CObj;

typedef list<CObj*>			OBJLIST;
typedef OBJLIST::iterator	OBJITER;

