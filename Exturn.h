#pragma once


#include "Struct.h"

extern HINSTANCE hInst;
extern HWND g_hWND;
extern HANDLE h_SendDataEvent;
extern HANDLE h_WriteDataEvent;

extern PlayerData playerDataPacket;

extern PlayerData* OtherPlayerData;

extern std::vector<MonsterData> v_Monster;
