#pragma once
#include "framework.h"
#include "Enum.h"
#include "Struct.h"


struct PlayerData
{
	INFO info;
<<<<<<< HEAD
	PLAYERSTATE playerState;
	//string name; // 캐릭터 위에 플레이 닉네임 표시용
	int playerHp;
	bool isDead; //요기 수정됨 alive->isDead로 수정
	Direction playerDir; //플레이어가 바라보는 방향   

	bool attakOn;
=======
	int playerState;
	//string name; // 캐릭터 위에 플레이 닉네임 표시용
	int playerHp;
	bool isDead; //요기 수정됨 alive->isDead로 수정
	int playerDir; //플레이어가 바라보는 방향   
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

	//RECT monsterAttEff; // 보스몬스터 공격 이펙트
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