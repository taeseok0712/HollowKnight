#pragma once
#include "framework.h"
#include "Packet.h"
extern HINSTANCE hInst;
extern HWND g_hWND;
extern int numOfPlayer;
extern HANDLE h_InitPlayerEvent;

extern PlayerData g_Player;
extern PlayerData g_Player2;
extern vector<MonsterData> v_Monster;
extern int numOfMonster;