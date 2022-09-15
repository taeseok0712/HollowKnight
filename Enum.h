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

//µô·¹ÀÌ¿ë
enum UpDown {UP,DOWN,SIDE};