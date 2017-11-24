#include "TcpServer.h"
#include <iostream>

int createSockFd()
{
    int fd = ::socket(AF_INET,SOCK_STREAM,0);
    if(fd == -1)
    {
        fprintf(stderr,"create sockfd failured\n");
        exit(EXIT_FAILURE);
    }
    return fd;
}

TcpServer::TcpServer(inetAddr & addr)
:sock_(createSockFd())
,epoll_(sock_.returnfd())
{
    sock_.bindAddress(addr);
    sock_.listen();
    std::cout << "tcpserver success" << std::endl;
}

