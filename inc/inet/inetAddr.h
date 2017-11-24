#ifndef INET_ADDR_H
#define INET_ADDR_H
#include "Noncopyable.h"
#include <netinet/in.h>
#include <string>

typedef struct sockaddr_in SAI;
class inetAddr:Noncopyable
{
    public:
        explicit inetAddr(const std::string &ip,int port);
        const struct sockaddr_in* getSockaddr()const
        {
            return &addr_;
        }
    private:
        struct sockaddr_in addr_;
};

#endif
