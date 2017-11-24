#include "Socket.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct sockaddr SA;
#define MAXCONN 10

Socket::Socket(int sockfd)
:fd_(sockfd)
{}

void Socket::bindAddress(const inetAddr & addr)
{
    if( -1 == ::bind(fd_,(SA*)addr.getSockaddr(),sizeof(addr)))
    {
        fprintf(stderr,"sockfd bind error\n");
        exit(EXIT_FAILURE);
    }
}

void Socket::listen()
{
    if( -1 == ::listen(fd_,MAXCONN))
    {
        fprintf(stderr,"sockfd listen error\n");
        exit(EXIT_FAILURE);
    }
    fprintf(stdout,"listen\n");
}

int Socket::accept()
{
    if( -1 == ::accept(fd_,NULL,NULL) )
    {
        fprintf(stderr,"sockfd accept error\n");
        exit(EXIT_FAILURE);
    }
}


