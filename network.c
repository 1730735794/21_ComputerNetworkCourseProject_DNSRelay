#include "protocol.h" //添加头文件
#define queuesize 127
int main()
{
    SOCKET sd = init_server();

    Recv_mes(sd);
    return 0;
}