#pragma warning(disable : 4996)
#pragma comment(lib, "ws2_32.lib")
#include "Server.h"
#include <conio.h>

Server::Server() {};
Server::~Server() {};
bool Server::ServerStart() {

	if (WSAStartup(MAKEWORD(2, 2), &m_WSAData) == NULL) {
		std::cout << "Server WSAStartup is successful\n";
		wsprintf(m_LogBuffer, "Server %s is %s", m_WSAData.szDescription, m_WSAData.szSystemStatus);
		m_WSAData.iMaxUdpDg = 512;
		//sendbuf = "testss string";
		
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
		int addr_accept_len = sizeof(m_client_addr);
		m_client_socket = accept(m_server_socket, (sockaddr*)&m_client_addr, &addr_accept_len);
		if (m_client_socket == INVALID_SOCKET) {
			std::cout << "Accept Error : " << WSAGetLastError() << std::endl;
			closesocket(m_server_socket);
			break;
		}
		else {
			std::cout << "Accepted.\n";
			SendFile();
		}
	}
};

void Server::SendFile() {
	file.open("picture.png", std::ios::binary | std::ios::in);
	if (file.is_open()) {
		// searcing begining of the file and its size
		file.seekg(0, file.end);
		long filesize = file.tellg();
		file.seekg(0,file.beg);
		//reading .png from file stream in buffer
		char* buffer = new char[filesize];
		file.read(buffer, filesize);
		//sending binary to client
		m_iResult = send(m_client_socket, buffer, filesize, 0);

		if (m_iResult == SOCKET_ERROR) {
			std::cout << "Send is failed. Error :" << WSAGetLastError() << std::endl;
			delete[] buffer;
			return;
		}
		else std::cout << "Sent bytes : " << m_iResult << std::endl;
		m_iResult = shutdown(m_client_socket, SD_SEND);
		if (m_iResult == SOCKET_ERROR)
		{
			std::cout << "Shutdown is failed. Error :" << WSAGetLastError() << std::endl;
			closesocket(m_client_socket);
			delete[] buffer;
			return;
		}
		else delete[] buffer;
	}
	else std::cout << "File didn't open. Error :" << GetLastError() << std::endl;
	file.close();
}
