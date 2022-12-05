#pragma once
#include "framework.h"
#include "Enum.h"


struct Info // ��ġ ���� �� ��µ� ������
{
	float fX;
	float fY;
	float fCX; //xũ��
	float fCY; //yũ��
};

struct PlayerData
{
	Info info;
	PLAYERSTATE playerState;
	string name; // ĳ���� ���� �÷��� �г��� ǥ�ÿ�
	int playerHp;
	bool playerAlive;
	Direction playerDir; //�÷��̾ �ٶ󺸴� ����   
};

struct MonsterData
{
	MONSTERTYPE monsterType;
	Info info;
	MONSTERSTATE monsterState;
	bool monsterAlive;
	Direction monsterDir;

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
