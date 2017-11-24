#include "SocketIO.h"
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

SocketIO::SocketIO(int fd)
:fd_(fd)
{}


int SocketIO::recv_peek(char * buf)
{
    int len;
    do
    {
        len = recv(fd_,buf,sizeof buf,MSG_PEEK);
    
    }while(len == -1 && errno == EINTR);
    return len;
}

int SocketIO::readn(char * buf,int len)
{
    int left = len;
    char *nbuf = buf;
    while(left >0)
    {
        int readn = ::read(fd_,nbuf,left);
        if(readn == -1 && errno == EINTR)
            continue;
        else if(readn == 0)
            break;
        left -= readn;
        nbuf += readn;
    }
    return len-left;
}

int SocketIO::read(char *buf ,int len)
{
    char * nbuf = buf;
    int left = len;
    while(left>0)
    {
        char bufp[1024];
        ::memset(bufp,0,sizeof(bufp));
        int readlen = recv_peek(bufp);
        
        if(readlen <=0)
            return readlen;
        else
        {
            for(int i=0;i<left;++i)
            {
                if(bufp[i] == '\n')
                {
                    int nsize = i+1;
                    if(readn(nbuf,nsize) != nsize)
                        return -1;
                    left -= nsize;
                    return len -left;
                }       
            
            }
        }
        if(readn(nbuf,readlen) != readlen)
            return -1;
        nbuf +=readlen;
        left -= readlen;
    }
    return len;
}

void SocketIO::send(const char * buf,int len)
{
    const char * nbuf = buf;
    int left = len;
    while(left > 0)
    {
        int num = ::write(fd_,buf,left);
        if(num == -1 && errno == EINTR)
            continue;
        if(num == 0)
            break;
        left -= num;
        nbuf +=num;
    }
}
