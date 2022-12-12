#pragma once

enum SCENEID {SCENE_LOGO, SCENE_MENU, SCENE_HELP, SCENE_STAGE1
, SCENE_STAGE2, SCENE_CLEAR,SCENE_END };

namespace ObjID
{
	enum ID
	{
		PLAYER,
		MONSTER,
		BULLET,
		SHIELD,
		BUTTON,
		MOUSE,
		END
	};
}

namespace GroupID
{
	enum ID { BACKGROUND, OBJECT, EFFECT, UI, END };
}

enum Direction { DR_LEFT, DR_RIGHT, DR_UP,DR_DOWN };

//�����̿�
enum UpDown {UP,DOWN,SIDE};

enum PLAYERSTATE
{
	STATE_ATT, STATE_IDLE, STATE_WALK, STATE_HIT,
	STATE_JUMP, STATE_FALL, STATE_LAND, STATE_DEAD,
	STATE_ATTD, STATE_ATTU
};

enum MONSTERTYPE
{
	BITTLE, BUG, FLY, HUSH, HUSHKNIGHT, BOSS, BITTLE2, BITTLE3, BITTLE4
};

enum MONSTERSTATE
{
	ATTACK, IDLE, WALK
};
enum KEYTYPE
{
	KEY_C, KEY_X, KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_UP,
};

enum MONSTERDIRECTION
{
	MDR_LEFT, MDR_RIGHT
};