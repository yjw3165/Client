#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <WinSock2.h>
#include <iostream>

using namespace std;

#pragma comment (lib, "ws2_32.lib")

int main()
{
	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "WinSock Error : " << GetLastError() << endl;
		exit(-1);
	}

	SOCKET ServerSocket;

	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);

	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error : " << GetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN ServerAddr;

	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(60000);
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "Connet Error : " << GetLastError() << endl;
		exit(-1);
	}


	char Buffer[1024] = { 0, };
	cin.getline(Buffer, 1023);
	send(ServerSocket, Buffer, strlen(Buffer) + 1, 0);

	int RecvLength = recv(ServerSocket, Buffer, 1024, 0);
	if (RecvLength == 0)
	{
		cout << "Close : " << endl;
		exit(-1);
	}
	else if (RecvLength < 0)
	{
		cout << "Error : " << endl;
		exit(-1);
	}

	cout << Buffer << endl;

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}