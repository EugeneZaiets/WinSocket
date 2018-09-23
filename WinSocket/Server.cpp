#include "Server.h"
#include <algorithm>
Server::Server() {};
Server::~Server() {};
bool Server::ServerStart() {
	m_sockets.reserve(4);
	m_addrs.reserve(4);
	m_port = 5000;
	for (int i = 0; i < 2; ++i) m_sockets[i] = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	for (int i = 2; i < 4; ++i) m_sockets[i] = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//m_WSAData.iMaxUdpDg
	for (int i = 0; i < m_addrs.size(); ++i) {
		m_addrs[i].sin_family = AF_INET;
		m_addrs[i].sin_port = htons(m_port);
	}
	m_addrs[0].sin_addr.S_un.S_addr = INADDR_BROADCAST;
	m_addrs[1].sin_addr.S_un.S_addr = inet_addr("192.168.0.101");
	m_addrs[2].sin_addr.S_un.S_addr = inet_addr("192.168.0.102");
	m_addrs[3].sin_addr.S_un.S_addr = inet_addr("192.168.0.103");

	if (WSAStartup(MAKEWORD(2, 2), &m_WSAData)) {
		std::cout << "Server started successfully\n";
	}
	else {
		std::cout << WSAGetLastError();
		std::cin.get();
		return false;
	}

	//wsprintf(m_LogBuffer, "Server %s %s", m_WSAData.szDescription, m_WSAData.szSystemStatus);

	for (int i = 0; i < m_sockets.size() && i < m_addrs.size(); ++i) {
		if (bind(m_sockets[i], (LPSOCKADDR)&m_addrs[i], sizeof(m_addrs[i])) == SOCKET_ERROR) {
			closesocket(m_sockets[i]);
			std::cout << "Error : " << WSAGetLastError();
			std::cin.get();
			return false;
		}
	}
	return true;
};
bool Server::ServerStop() {
	for (SOCKET socket : m_sockets) {
		if(closesocket(socket) == SOCKET_ERROR) {
			std::cout << "Error : " << WSAGetLastError();
			std::cin.get();
			return false;
		}
	}
	WSACleanup();
	return true;
};
void Server::handle() {};