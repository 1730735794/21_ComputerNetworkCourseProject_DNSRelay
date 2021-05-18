#include<stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")//添加头文件
#define queuesize 127
SOCKET init_server()
{
    //初始化
    WORD wdVersion = MAKEWORD(2, 2);//定义自己需要的网络库版本
	WSADATA wdSockMsg;//这是一个结构体
	if(WSAStartup(wdVersion, &wdSockMsg) != 0)
        printf("WSAStartup error: %s(errno: %d)/n",strerror(errno),errno);
    //创建套接字
    SOCKET sd;
    sd = socket(PF_INET,SOCK_DGRAM,0);
    return sd;
}
void send_mes(SOCKET sd)
{
    char *send_mes = malloc(sizeof(char) * 128);
    memset(send_mes,0,sizeof(send_mes));
    send_mes[0] = 20; //给send赋值

    SOCKADDR_IN send_to_addr;
    send_to_addr.sin_family = AF_INET;
    send_to_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    send_to_addr.sin_port = 53;

    if(sendto(sd,send_mes,sizeof(*send_mes),0,(SOCKADDR * )&send_to_addr,sizeof(SOCKADDR_IN)) >= 0)
        printf("%d\n",send_mes[0]);
    // printf("%d", GetLastError());//检查错误的函数
}
int main()
{
    SOCKET sd = init_server();
    //接收数据
        send_mes(sd);

    return 0;
}