#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <WinSock2.h>
#include <winsock.h>

class Server {
	WSADATA m_WSAData;
	HWND hWnd;
	SOCKET m_server_socket, m_client_socket;
	sockaddr_in m_server_addr, m_client_addr;
	unsigned short m_port = 8888;
	char m_LogBuffer[128];
	char recvbuffer[512] = "";
	int partnum = 0;
public:
	int m_iResult;
	const char* sendbuf = nullptr;
	std::ifstream file;
	unsigned char key = 0;
	Server();
	~Server();
	bool ServerStart();
	bool ServerStop();
	void handle();
	void SendFile();
};
