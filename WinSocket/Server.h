#pragma once
#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <winsock.h>

class Server {
	WSADATA m_WSAData;
	SOCKET m_server_socket;
	sockaddr_in m_server_addr;
	unsigned short m_port = 8888;
public:
	unsigned char key = 0;
	char m_LogBuffer[128];
	Server();
	~Server();
	bool ServerStart();
	bool ServerStop();
	void handle();
};
