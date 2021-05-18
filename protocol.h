#include<stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")
SOCKET init_server();
void Recv_mes(SOCKET sd);
