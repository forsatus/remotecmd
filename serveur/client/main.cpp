#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

using namespace std;

const char* ipDuServeur = "127.0.0.1";
int portDuServeur = 6643;

int main()
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);
	//
	SOCKET sock;
	SOCKADDR_IN sin;
	sin.sin_addr.s_addr = inet_addr(ipDuServeur);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(portDuServeur);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	bind(sock, (SOCKADDR *)&sin, sizeof(sin));
	if (connect(sock, (SOCKADDR *)&sin, sizeof(sin)) == 0)
	{

		while (true)
		{
			char buffer[255];
			int etatDuPaquetRecu = recv(sock, buffer, sizeof(buffer), 0);
			if (etatDuPaquetRecu != SOCKET_ERROR && etatDuPaquetRecu > 0)
			{
				cout << buffer << endl;
			}

		}
	}
	//
	WSACleanup();
	return 0;
}