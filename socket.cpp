#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")  //╪сть ws2_32.dll

#define BUF_SIZE 1024
#pragma warning(disable : 4996)
int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    
    SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    
    sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(30012);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    char bufSend[BUF_SIZE] = { 0 };
    printf(">>  ");
    scanf("%s", bufSend);
    char endc[1] = { '\n' };
    strncat(bufSend, endc, 1);
    send(sock, bufSend, strlen(bufSend), 0);
    
    char bufRecv[BUF_SIZE] = { 0 };
    recv(sock, bufRecv, BUF_SIZE, 0);

    
    printf("<<  %s\n", bufRecv);

    char bufRecv2[BUF_SIZE] = { 0 };
    recv(sock, bufRecv2, BUF_SIZE, 0);


    printf("<<  %s\n", bufRecv2);

    closesocket(sock);

    WSACleanup();

    system("pause");
    return 0;
}

