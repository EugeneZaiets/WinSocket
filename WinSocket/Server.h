#pragma once
#include <iostream>
#include <vector>
#include <WinSock2.h>
#include <winsock.h>

class Server {
	WSADATA m_WSAData;
	SOCKET m_server_socket;
	std::vector<SOCKET> m_sockets;
	std::vector<sockaddr_in> m_addrs;
	unsigned short m_port = 8888;
public:
	char m_LogBuffer[128];
	Server();
	~Server();
	bool ServerStart();
	bool ServerStop();
	void handle();
};
