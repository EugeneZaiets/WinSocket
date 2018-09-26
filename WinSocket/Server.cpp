#include "Server.h"
#include <algorithm>
#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")

Server::Server() {};
Server::~Server() {};
bool Server::ServerStart() {
	if (WSAStartup(MAKEWORD(2, 2), &m_WSAData) == NULL) {
		std::cout << "Server WSAStartup is successful\n";
		wsprintf(m_LogBuffer, "Server %s is %s", m_WSAData.szDescription, m_WSAData.szSystemStatus);
		m_WSAData.iMaxUdpDg = 123;
		std::cout << "iMaxUdpDg size : " << m_WSAData.iMaxUdpDg << " bytes." << std::endl;
		std::cout << m_LogBuffer << std::endl;
	}
	else {
		std::cout << "WSAStartUp Error : " << WSAGetLastError();
		std::cin.get();
		return false;
	}

	for (unsigned int i = 0; i < 2; ++i) {
		m_sockets.push_back(socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP));
		if (m_sockets[i] == INVALID_SOCKET)
			std::cout << "Error : INVALID_SOCKET[" << i << "] | Last Error : " << WSAGetLastError() << "\n";
	}
	for (unsigned int i = 2; i < 4; ++i) {
		m_sockets.push_back(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP));
		if (m_sockets[i] == INVALID_SOCKET)
			std::cout << "Error : INVALID_SOCKET[" << i << "] | Last Error : " << WSAGetLastError() << "\n";
	}
	for (unsigned int i = 0; i < 4; ++i) {
		m_addrs.push_back(sockaddr_in());
		m_addrs[i].sin_family = AF_INET;
		m_addrs[i].sin_port = htons(m_port);
	}
	m_addrs[0].sin_addr.S_un.S_addr = INADDR_BROADCAST;
	m_addrs[1].sin_addr.S_un.S_addr = inet_addr("192.168.0.102");
	m_addrs[2].sin_addr.S_un.S_addr = inet_addr("192.168.0.103");
	m_addrs[3].sin_addr.S_un.S_addr = inet_addr("192.168.0.104");
	for (unsigned int i = 0; i < 4; ++i) {
		if (bind(m_sockets[i], (sockaddr*)&m_addrs[i], sizeof(m_addrs[i])) == SOCKET_ERROR) {
			std::cout << "Bind Error : " << WSAGetLastError() << std::endl;
			closesocket(m_sockets[i]);
			//return false;
		}
		else std::cout << "Binding of socket[" << i << "] is successful.\n";
	}

	PHOSTENT phe;
	phe = gethostbyname("www.ZEWinSock.com");
	if (phe == NULL) {

		std::cout << "GetHostByName Error : " << WSAGetLastError() << std::endl;
		return false;
	}
	memcpy((char FAR*)&m_addrs[1].sin_addr, phe->h_addr_list[0], phe->h_length);
	std::cout << "IP-Address of domain - www.ZEWinSock.com :: "<< inet_ntoa(m_addrs[1].sin_addr) << std::endl;
	return true;

};
bool Server::ServerStop() {
	for (SOCKET socket : m_sockets) {
		if(closesocket(socket) == SOCKET_ERROR) {
			if (WSAGetLastError() == 10038) {
				std::cout << "Socket has already beed CLOSED (or invalid).\n";
				continue;
			}
			std::cout << "Close Error : " << WSAGetLastError();
		}
	}
	std::cin.get();
	WSACleanup();
	return true;
};
void Server::handle() {};