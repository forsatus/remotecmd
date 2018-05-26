#include <WinSock2.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

using namespace std;

unsigned long ipDuServeur = inet_addr("82.228.178.236");
u_short portDuServeur = htons(6643);

int main() {
  SetConsoleOutputCP(65000);
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
  while (true) {
    string paquet;
    char hostname[255];
    unsigned long tailleBuf = 255;

    if (GetComputerName(hostname, &tailleBuf) == 1)
      paquet = hostname;

    send(socketServeur, paquet.c_str(), paquet.size() + 1, 0);
    int n = recv(socketServeur, buffer, sizeof(buffer), 0);
    buffer[n] = '\0';
    cout << buffer << endl;
  }
  closesocket(socketServeur);
  WSACleanup();
  system("pause");
  return 0;
}
