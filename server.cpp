/*
	Simple UDP Server
*/

#include<stdio.h>
#include<winsock2.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 32	//Max length of buffer
#define PORT 8080	//The port on which to listen for incoming data

struct Acilar_t
{
	double aci1;
	double aci2;
	double anaaci;
	double anaaci2;
} ;

int main()
{
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen, recv_len;
	char buf[BUFLEN];
	WSADATA wsa;

	slen = sizeof(si_other);

	Acilar_t onemli_acilar;
	onemli_acilar.aci1 = 40;
	onemli_acilar.aci2 = 80;
	onemli_acilar.anaaci = 60;
	onemli_acilar.anaaci2 = 90;

	char* onemli_acilar_bytes = reinterpret_cast<char*>(&onemli_acilar);


	//Initialise winsock
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}
	printf("Socket created.\n");

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Bind
	if (bind(s, (struct sockaddr*)&server, sizeof(server)) == SOCKET_ERROR)
	{
		printf("Bind failed with error code : %d", WSAGetLastError());
		exit(EXIT_FAILURE);
	}
	puts("Bind done");

	//keep listening for data
	while (1)
	{
		printf("Waiting for data...");
		fflush(stdout);

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//print details of the client/peer and the data received

		printf("Data: %s\n", buf);

		//now reply the client with the same data
		if (sendto(s, onemli_acilar_bytes, BUFLEN, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	closesocket(s);
	WSACleanup();

	return 0;
}
