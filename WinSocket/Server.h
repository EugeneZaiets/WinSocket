#pragma once
#include <iostream>
#include <WinSock2.h>
#include <winsock.h>

class Server {
	SOCKET m_server_socket;
	SOCKET m_socket_dg_1, m_socket_dg_2;
	SOCKET m_socket_vchanel_1, m_socket_vchanel_2;
	WSADATA m_WSAData;
public:
	char m_LogBuffer[128];
	Server();
	~Server();
	bool ServerStart();
	bool ServerStop();
	void handle();
};
