#pragma once
#include "framework.h"
#include "Enum.h"
#include "Struct.h"


struct PlayerData
{
	INFO info;
	PLAYERSTATE playerState;
	string name; // 캐릭터 위에 플레이 닉네임 표시용
	int playerHp;
	bool isDead; //요기 수정됨 alive->isDead로 수정
	Direction playerDir; //플레이어가 바라보는 방향   
};

struct MonsterData
{
	int monsterNum;
	MONSTERTYPE monsterType;
	INFO info;
	MONSTERSTATE monsterState;
	bool isDead;
	MONSTERDIRECTION monsterDir;

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

typedef list<CObj*>			OBJLIST;
typedef OBJLIST::iterator	OBJITER;