#pragma once
#include "Global.h"
#include "Enum.h"


struct Info // 위치 정보 및 출력될 사이즈
{
	float fX;
	float fY;
	float fCX; //x크기
	float fCY; //y크기
};

struct PlayerData
{
	Info info;
	PLAYERSTATE playerState;
	string name; // 캐릭터 위에 플레이 닉네임 표시용
	int playerHp;
	bool playerAlive;
	DIR playerDir; //플레이어가 바라보는 방향   
};

struct MonsterData
{
	MONSTERTYPE monsterType;
	Info info;
	MONSTERSTATE monsterState;
	bool monsterAlive;
	DIR monsterDir;

	RECT monsterAttEff; // 보스몬스터 공격 이펙트
};

struct KeyInfo
{
	bool keyUp; // 키up시 true ,down시 False
	KEYTYPE keyType;
};

struct ClientInfo
{
	SCENEID SceneId;
	string PlayerIP;
	string name;
	bool isReady;
};
