#pragma once
#include "Common.h"
#include "Packet.h"
#include "framework.h"
#include "Player.h"

class Client {
public:
	SOCKET sock;
	bool m_isconnected = false;
	Info info;
	PLAYERSTATE PlayerState;
	int hp;
public:
	Client()
	{
		m_isconnected = false;
		info.fX = 0;
		info.fY = 0;
		PlayerState = STATE_IDLE;
		hp = 6;
	}
};

extern array <Client, MAXPLAYERNUM> g_clients;