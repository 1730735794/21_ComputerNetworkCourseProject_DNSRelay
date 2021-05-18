#include "protocol.h"
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

    SOCKADDR_IN address;
    memset(&address,0,sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");//指定通配IP 0.0.0.0
    address.sin_port = 53;
    if(bind(sd,(struct sockaddr *)&address, sizeof(struct sockaddr)) == -1)
        printf("bind socket error: %s(errno: %d)/n",strerror(errno),errno);//指定端口号
    return sd;
}
void Recv_mes(SOCKET sd)
{
    char *recv = malloc(sizeof(char) * 128);
    SOCKADDR_IN recv_addr;
    int addr_len = sizeof(SOCKADDR_IN);
    if(recvfrom(sd,recv,sizeof(char) * 128,0,(SOCKADDR *)&recv_addr,&addr_len) >= 0)
        printf("%d",recv[0]);
    return 0;
}
