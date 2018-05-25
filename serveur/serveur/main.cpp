#include <iostream>
#include <string>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

using namespace std;

u_short portDuServeur = htons(6643);

int main() {
  SetConsoleOutputCP(65000);
  WSADATA WSAData;
  SOCKET sock;
  SOCKET csock;
  SOCKADDR_IN sin;
  SOCKADDR_IN csin;
  WSAStartup(MAKEWORD(2, 0), &WSAData);
  sock = socket(AF_INET, SOCK_STREAM, 0);
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_family = AF_INET;
  sin.sin_port = portDuServeur;
  bind(sock, (SOCKADDR *)&sin, sizeof(sin));
  listen(sock, 0);
  char buffer[255];
  while (true) {
    int sinsize = sizeof(csin);
    if ((csock = accept(sock, (SOCKADDR *)&csin, &sinsize)) != INVALID_SOCKET) {
      cout << "Client connecté" << endl;
      int n = recv(csock, buffer, sizeof(buffer), 0);
      buffer[n] = '\0';
      string nomDuPcClient = buffer;
      while (true) {
        cout << nomDuPcClient << " : ";
        string paquet;
        getline(cin, paquet);
        send(csock, paquet.c_str(), paquet.size() + 1, 0);
      }
      closesocket(csock);
    }
  }
  system("pause");
  return 0;
}
