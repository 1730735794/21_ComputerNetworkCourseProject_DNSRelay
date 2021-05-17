#include <stdio.h>
#include <string.h>
int is_ip_addr(char *s);
void str_to_ip(unsigned char ip[4], char* string);
int config(int argc, char *argv[]);

FILE *cache_file = NULL;
int debug_level = 0;
unsigned char dns_server_ipaddr[4] = {8, 8, 8, 8};

int main(int argc, char *argv[])
{
    if(config(argc, argv))
        return 1;

    //以下为参数调试用
    // printf("%d\n", debug_level);
    // for (int i = 0; i < 4; i++)
    //     printf("%d  ", dns_server_ipaddr[i]);
    // printf("\n");
    // printf("%s\n", cache_file->_tmpfname);
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
        else if (is_ip_addr(argv[i]))
            str_to_ip(dns_server_ipaddr, argv[i]);
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

int is_ip_addr(char *s)
{
    unsigned int tmp = 0;
    int dot_cnt = 0;
    for (int i = 0;; i++)
    {
        if (s[i] == '.' || s[i] == '\0')
        {
            if (tmp > 255 || tmp < 0)
                return 0;
            else
                tmp = 0;
            if (s[i] == '\0')
                break;
            else
                dot_cnt++;
        }
        else if (s[i] > '9' || s[i] < '0')
            return 0;
        else
        {
            tmp *= 10;
            tmp += s[i] - '0';
        }
    }
    if (dot_cnt != 3)
        return 0;
    return 1;
}

void str_to_ip(unsigned char ip[4], char* string)
{
    int byte_num = 0;
    unsigned char tmp = 0;
    for (int i = 0;; i++)
    {
        if (string[i] == '.' || string[i] == '\0')
        {
            ip[byte_num] = tmp;
            tmp = 0;
            byte_num++;
            if (string[i] == '\0')
                break;
        }
        else
        {
            tmp *= 10;
            tmp += string[i] - '0';
        }
    }
}