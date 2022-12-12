#pragma once


#include "Struct.h"

extern HINSTANCE hInst;
extern HWND g_hWND;
extern HANDLE h_SendDataEvent;
extern HANDLE h_WriteDataEvent;
extern HANDLE h_InitMonsterEvent;
extern HANDLE h_ConnectServerEvent;



extern SCENEID CUR_SCENE;
extern SCENEID NEXT_SCENE;
extern string SERVER_IP;
extern string NickName;

extern bool ENDFLAG;

//extern SCENEID SID;

extern PlayerData playerDataPacket;

extern PlayerData OtherPlayerData;

extern std::vector<MonsterData> v_Monster;

extern int waveNum;