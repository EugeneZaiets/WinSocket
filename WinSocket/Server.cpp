#include "Server.h"

Server::Server() {};
Server::~Server() {};
bool Server::ServerStart() {
	if (WSAStartup(MAKEWORD(2, 2), &m_WSAData)) {
		std::cout << "Server started successfully\n";
	}
	else {
		std::cout << WSAGetLastError();
		std::cin.get();
	}
	wsprintf(m_LogBuffer, "Server %s %s", m_WSAData.szDescription, m_WSAData.szSystemStatus);
	return true;
};
bool Server::ServerStop() {
	WSACleanup();
	return true;
};
void Server::handle() {};