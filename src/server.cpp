#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include "server.h"
#include <ctime>
using namespace Fourier;
using namespace std;

int Fourier::server()
{
  int iResult = 0;

  // * Konstanter
  WSADATA wsaData;
  int family = AF_INET;
  int type = SOCK_STREAM;
  int protocol = IPPROTO_TCP;

  // * Variablar
  SOCKET sck = INVALID_SOCKET;
  sockaddr_in service;

  // * Init WinSock
  // ! Inget funkar utan denna
  iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (iResult != NO_ERROR)
  {
    wprintf(L"Error at WSAStartup()\n");
    return 1;
  }

  // * Init Socket med domän (IPV4), typ (stream), Protocol (tcp)
  sck = socket(family, type, protocol);
  if (sck == INVALID_SOCKET)
  {

    wprintf(L"socket function failed with error: %u\n", WSAGetLastError());
    WSACleanup();
    return 1;
  }

  // * Adress och port (0: låt systemet välja)
  // ? htons = vanligt nummer till tcp nummer??
  service.sin_family = AF_INET;
  service.sin_addr.s_addr = inet_addr("127.0.0.1");
  service.sin_port = htons(5000); // 0);

  // * Koppla socket till adressen
  iResult = bind(sck, (SOCKADDR *)&service, sizeof(service));
  if (iResult == SOCKET_ERROR)
  {
    wprintf(L"bind failed with error %u\n", WSAGetLastError());
    closesocket(sck);
    WSACleanup();
    return 1;
  }
  else
  {
    wprintf(L"bind returned success\n");
  }

  if (listen(sck, SOMAXCONN) == SOCKET_ERROR)
  {
    wprintf(L"listen function failed with error: %d\n", WSAGetLastError());
    closesocket(sck);
    return 1;
  }

  iResult = callback(sck);
  if (iResult = SOCKET_ERROR)
  {
    closesocket(sck);
    return 1;
  }

  closesocket(sck);
  WSACleanup();
  return 0;
}

int Fourier::callback(SOCKET sck)
{
  sockaddr addrOut;
  int addrLen = sizeof(addrOut);
  getsockname(sck, &addrOut, &addrLen);
  struct sockaddr_in *in_addrOut = (struct sockaddr_in *)&addrOut;
  uint16_t port;

  port = htons(in_addrOut->sin_port);
  cout << "Socket listening on port: " << port << endl;

  sockaddr client_addr;
  int client_len = sizeof(client_addr);

  SOCKET acc_sck = accept(sck, &client_addr, &client_len);
  if (acc_sck == INVALID_SOCKET)
  {
    wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
    WSACleanup();
    return SOCKET_ERROR;
  }
  else
  {
    wprintf(L"Client connected.\n");
  }

  char buf[1024];

  int iResult = recv(acc_sck, buf, 1024, 0);
  if (iResult > 0)
  {
    printf("Bytes received: %d\n", iResult);
    cout << time(NULL) << endl;
    cout << buf[0] << ":" << (unsigned int)(0xFF) << " or " << (unsigned int)((char)(0xF) + (char)(0xF)) << " and " << buf[1] << ":" << (unsigned int)buf[1] << " = " << (unsigned int)(0 | buf[0]) << " and " << (unsigned int)(0 | buf[1]) << " and " << ((unsigned int)buf[0] << 8 | (unsigned int)buf[1]) << endl;
  }
  else if (iResult == 0)
  {
    printf("Connection closed\n");
  }
  else
  {
    printf("recv failed: %d\n", WSAGetLastError());
  }
  return 0;
}