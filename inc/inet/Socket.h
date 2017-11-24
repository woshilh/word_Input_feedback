#ifndef SOCKET_H
#define SOCKET_H

#include "Noncopyable.h"
#include "inetAddr.h"

class Socket : Noncopyable
{
    public:
        Socket(int sockfd);
        void bindAddress(const inetAddr &);
        void listen();
        int accept();
        
        int returnfd()
        {
            return fd_;
        }
    private:
        const int fd_;
};

#endif
