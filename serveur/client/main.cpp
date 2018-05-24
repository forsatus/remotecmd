#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

using namespace std;

unsigned long ipDuServeur = inet_addr("127.0.0.1");
u_short portDuServeur = htons(6643);

int main() {
	WSADATA WSAData;
	SOCKET socketServeur;
	SOCKADDR_IN sin;
	char buffer[255];
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	socketServeur = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_addr.s_addr = ipDuServeur;
	sin.sin_family = AF_INET;
	sin.sin_port = portDuServeur;
	connect(socketServeur, (SOCKADDR *)&sin, sizeof(sin));

	int n = recv(socketServeur, buffer, sizeof(buffer), 0);
	buffer[n] = '\0';
	cout << buffer << endl;
	closesocket(socketServeur);
	WSACleanup();
	system("pause");
	return 0;
}
