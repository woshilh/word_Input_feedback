#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "Noncopyable.h"
#include "inetAddr.h"
#include "Epoller.h"
#include "TcpConnect.h"
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


class TcpServer : Noncopyable
{
    public:
        TcpServer(inetAddr & addr);
        ~TcpServer()
        {
        }
        void start()
        {
            epoll_.loop();
        }

        void setConnectCB( TcpConnectCallback cb)
        {
            epoll_.setConnectCB(std::move(cb));
        }
        
        void setMessageCB( TcpConnectCallback cb)
        {
            epoll_.setMessageCB(std::move(cb));
        }
        
        void setCloseCB( TcpConnectCallback cb)
        {
            epoll_.setCloseCB(std::move(cb));
        }

    private:
        Socket sock_;
        Epoller epoll_;
};

#endif
