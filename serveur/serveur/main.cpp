#include <WinSock2.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)

using namespace std;

u_short portDuServeur = htons(6643);

int envoyerUnPaquet(SOCKET destinataire, string paquetAEnvoyer);
string recevoirUnPaquet(SOCKET serveur);
void saisie(SOCKET destinataire);

string nomDuPcClient;

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

  while (true) {
    int sinsize = sizeof(csin);
    if ((csock = accept(sock, (SOCKADDR *)&csin, &sinsize)) != INVALID_SOCKET) {
      nomDuPcClient = recevoirUnPaquet(csock);
      cout << "Client connecté avec l'ip : " << inet_ntoa(csin.sin_addr) << endl;


      saisie(csock);

      closesocket(csock);
    }
  }
  system("pause");
  return 0;
}

int envoyerUnPaquet(SOCKET destinataire, string paquetAEnvoyer) {
  send(destinataire, paquetAEnvoyer.c_str(), paquetAEnvoyer.size() + 1, 0);
  return 0;
}

string recevoirUnPaquet(SOCKET serveur) {
  char buffer[500];
  int n = recv(serveur, buffer, sizeof(buffer), 0);
  buffer[n] = '\0';
  return buffer;
}

void saisie(SOCKET destinataire) {
  while (true) {
    cout << nomDuPcClient << " : " << flush;
    string paquet;
    getline(cin, paquet);
    envoyerUnPaquet(destinataire, paquet);
  }
}
