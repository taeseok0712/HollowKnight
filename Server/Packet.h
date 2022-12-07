#pragma once
#include "framework.h"
#include "Enum.h"
#include "Struct.h"


struct PlayerData
{
	INFO info;
	PLAYERSTATE playerState;
	string name; // ĳ���� ���� �÷��� �г��� ǥ�ÿ�
	int playerHp;
	bool isDead; //��� ������ alive->isDead�� ����
	Direction playerDir; //�÷��̾ �ٶ󺸴� ����   
};

struct MonsterData
{
	int monsterNum;
	MONSTERTYPE monsterType;
	INFO info;
	MONSTERSTATE monsterState;
	bool isDead;
	MONSTERDIRECTION monsterDir;

	RECT monsterAttEff; // �������� ���� ����Ʈ
};

struct KeyInfo
{
	bool keyUp; // Űup�� true ,down�� False
	KEYTYPE keyType;
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