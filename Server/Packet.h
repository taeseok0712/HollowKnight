#pragma once
#include "framework.h"
#include "Enum.h"
#include "Struct.h"


struct PlayerData
{
	INFO info;
	int playerState;
	//string name; // ĳ���� ���� �÷��� �г��� ǥ�ÿ�
	int playerHp;
	bool isDead; //��� ������ alive->isDead�� ����
	int playerDir; //�÷��̾ �ٶ󺸴� ����   
};

struct MonsterData
{
	//int monsterNum;
	MONSTERTYPE monsterType;
	INFO info;
	MONSTERSTATE monsterState;
	bool isDead;
	int monsterDir;

	//RECT monsterAttEff; // �������� ���� ����Ʈ
};

struct ClientInfo
{
	SCENEID SceneId;
	string PlayerIP;
	string name;
	bool isReady;
};

typedef list<CObj*>			OBJLIST;
typedef OBJLIST::iterator	OBJITER;