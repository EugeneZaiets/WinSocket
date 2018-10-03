#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <WinSock2.h>
#include <winsock.h>

class Server {
	WSADATA m_WSAData;
	SOCKET m_server_socket, m_client_socket;
	sockaddr_in m_server_addr, m_client_addr;
	unsigned short m_port = 8888;
public:
	int m_iResult;
	const char* sendbuf = nullptr;
	std::ifstream* file;
	FILE* testfile;
	unsigned char key = 0;
	char m_LogBuffer[128];
	char recvbuffer[512] = "";
	Server();
	~Server();
	bool ServerStart();
	bool ServerStop();
	void handle();
	void SendFile();
};
