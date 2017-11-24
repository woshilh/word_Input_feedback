#include "inetAddr.h"
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>


inetAddr::inetAddr(const std::string & ip,int port)
{
    ::memset(&addr_,0,sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    if(inet_aton(ip.c_str(),&addr_.sin_addr) == 0)
    {
        fprintf(stderr,"ip invalid\n");
        exit(EXIT_FAILURE);
    }
}
