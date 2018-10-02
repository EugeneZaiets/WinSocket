#include "Server.h"
#include <conio.h>
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
	m_server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_server_socket == INVALID_SOCKET)
		std::cout << "Error : INVALID_SOCKET| Last Error : " << WSAGetLastError() << "\n";

	m_server_addr.sin_family = AF_INET;
	m_server_addr.sin_port = htons(m_port);

	PHOSTENT phe;
	phe = gethostbyname("localhost");
	if (phe == NULL) {

		std::cout << "GetHostByName Error : " << WSAGetLastError() << std::endl;
		return false;
	}
	memcpy((char FAR*) &m_server_addr.sin_addr , phe->h_addr_list[0], phe->h_length);
	std::cout << "IP-Address of domain - localhost :: " << inet_ntoa(m_server_addr.sin_addr) << std::endl;

	if (bind(m_server_socket, (sockaddr*)&m_server_addr, sizeof(m_server_addr)) == SOCKET_ERROR) {
		std::cout << "Bind Error : " << WSAGetLastError() << std::endl;
		closesocket(m_server_socket);
	} else std::cout << "Binding of socket is successful.\n";

	if (listen(m_server_socket, 1) == SOCKET_ERROR) {
		std::cout << "Listen Error : " << WSAGetLastError() << std::endl;
		closesocket(m_server_socket);
	} else std::cout << "Listening...\n";
	handle();
	return true;
};
bool Server::ServerStop() {
	if(closesocket(m_server_socket) == SOCKET_ERROR) {
		if (WSAGetLastError() == 10038) {
			std::cout << "Socket has already beed CLOSED (or invalid).\n";
		}
		std::cout << "Close Error : " << WSAGetLastError();
	}
	std::cin.get();
	WSACleanup();
	return true;
};
void Server::handle() {
	while (true) {
		key = getch();
		if (key == 27) break;
		SOCKET accepted;
		sockaddr_in addr_accept;
		int addr_accept_len = sizeof(addr_accept);
		if ((accepted = accept(m_server_socket, (sockaddr*)&addr_accept, &addr_accept_len) != 0)) {
			std::cout << "Connected. IP:"
				<< (unsigned char)addr_accept.sin_addr.S_un.S_un_b.s_b1 << "."
				<< (unsigned char)addr_accept.sin_addr.S_un.S_un_b.s_b2 << "."
				<< (unsigned char)addr_accept.sin_addr.S_un.S_un_b.s_b3 << "."
				<< (unsigned char)addr_accept.sin_addr.S_un.S_un_b.s_b4 << std::endl;
		}
		
	}
};
