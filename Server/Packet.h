#pragma once
#include "framework.h"
#include "Enum.h"
#include "Struct.h"


struct PlayerData
{
	INFO info;
<<<<<<< HEAD
	PLAYERSTATE playerState;
	//string name; // ĳ���� ���� �÷��� �г��� ǥ�ÿ�
	int playerHp;
	bool isDead; //��� ������ alive->isDead�� ����
	Direction playerDir; //�÷��̾ �ٶ󺸴� ����   

	bool attakOn;
=======
	int playerState;
	//string name; // ĳ���� ���� �÷��� �г��� ǥ�ÿ�
	int playerHp;
	bool isDead; //��� ������ alive->isDead�� ����
	int playerDir; //�÷��̾ �ٶ󺸴� ����   
>>>>>>> ccd12ab2419cce183e7638c8d55a527d50ead7ca
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