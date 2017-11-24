#ifndef TCPCONNECT_H
#define TCPCONNECT_H

#include "Noncopyable.h"
#include "Socket.h"
#include "SocketIO.h"
#include <string>
#include <memory>
#include <functional>

class TcpConnect;
typedef std::shared_ptr<TcpConnect> TcpConnectPtr;
typedef std::function<void (const TcpConnectPtr & )> TcpConnectCallback;

class TcpConnect : Noncopyable,
                   public std::enable_shared_from_this<TcpConnect>
{
    public:
        
        TcpConnect(int fd);

        void setConnectCB(TcpConnectCallback cb)
        {
            connectCallback_ = std::move(cb);
        }
        void setMessageCB(TcpConnectCallback  cb)
        {
            messageCallback_ = std::move(cb);
        }
        void setCloseCB(TcpConnectCallback  cb)
        {
            closeCallback_ = std::move(cb);
        }
        
        const char* receive();
        void send(const std::string &str);

        void handleConnectCallback();
        void handleMessageCallback();
        void handleCloseCallback();
        int fd()
        {
            return sock_.returnfd();
        }
   private:
        Socket sock_;
        SocketIO sockIO_;

        TcpConnectCallback connectCallback_;
        TcpConnectCallback messageCallback_;
        TcpConnectCallback closeCallback_;

};

#endif
