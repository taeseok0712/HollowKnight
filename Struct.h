#pragma once
typedef struct tagInfo
{
	float fX;
	float fY;
	float fCX; //xũ��
	float fCY; //yũ��
}INFO;


typedef struct tagFrame
{
	int iFrameStart; // ��������Ʈ x ���� ����. 
	int iFrameEnd; // ��������Ʈ y�హ�� 
	int iFrameScene; // ��������Ʈ ���� 
	DWORD dwFrameSpeed;
	DWORD dwFrameTime; // ����� �ʿ��� �ð�. 
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


struct PlayerData
{
	INFO info;
	int playerState;
	//string name; //���߿� �߰��ϱ����� �ϴ� �����ص�
	int playerHp; 
	bool isDead; //��� ������ alive->isDead�� ����
	int playerDir; //�÷��̾ �ٶ󺸴� ����
	//TCHAR* FrameKey;
};


