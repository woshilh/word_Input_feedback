#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char **argv)
{
    if(argc != 3)
    {
        printf("args error\n");
        exit(EXIT_FAILURE);
    }
    int fd = socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        printf("socket error\n");
        exit(EXIT_FAILURE);
    }
    struct sockaddr_in addr_;
    addr_.sin_family = AF_INET;
    int port;
    sscanf(argv[2],"%d",&port);
    addr_.sin_port = htons(port);
    addr_.sin_addr.s_addr = inet_addr(argv[1]);
    
    if(-1 == connect(fd,(struct sockaddr*)&addr_,sizeof addr_))
    {
        perror("connect error");
        exit(EXIT_FAILURE);
    }
    while(2);
   
    return 0;

}
