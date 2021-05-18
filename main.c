#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
//#include <netinet/in.h>
#include <arpa/inet.h>
int is_ip_addr(char *s);
void str_to_ip(unsigned char ip[4], char* string);
int config(int argc, char *argv[]);

FILE *cache_file = NULL;
int debug_level = 0;
struct in_addr dns_server_ipaddr;

int main(int argc, char *argv[])
{
    if(config(argc, argv))
        return 1;

    //以下为参数调试用
    printf("%d\n", debug_level);
    printf("%u\n", dns_server_ipaddr);
}

int config(int argc, char *argv[])
{
    if (argc == 1)
        cache_file = fopen("dnsrelay.txt", "r");
    for (int i = 1; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
            debug_level = 1;
        else if (strcmp(argv[i], "-dd") == 0)
            debug_level = 2;
        else if (inet_addr(argv[i]) != INADDR_NONE)
            dns_server_ipaddr.s_addr = inet_addr(argv[i]); 
        else if ((cache_file = fopen(argv[i], "r")) == NULL)
        {
            printf("Wrong args, exiting...\n");
            printf("Help:\n");
            printf("\tdnsrelay [-d|-dd] [dns-server-ipaddr] [filename]\n");
            return 1;
        }
    }
    return 0;
}