#include "Server.h"
int main()
{
	Server server;
	if (server.ServerStart()) {
		std::cout << "Server has been run successfully.\n";
	} else {
		std::cout << "Server has NOT been run.\n";
	}
	if (server.ServerStop()){
		std::cout << "Server has been shut down successfully.\n";
		std::cin.get();
	} else {
		std::cout << "\bServer has NOT been shut down successfully.\n";
		std::cin.get();
	};
	return 0;
}