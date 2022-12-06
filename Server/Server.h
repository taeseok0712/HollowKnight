#pragma once
#include "Common.h"
#include "Packet.h"
#include "framework.h"
#include "Player.h"

class Client {
public:
	SOCKET sock;
	bool m_isconnected = false;
};
