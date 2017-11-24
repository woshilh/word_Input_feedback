#ifndef EPOLLER_H
#define EPOLLER_H

#include "Noncopyable.h"
#include "TcpConnect.h"
#include <vector>
#include <map>
#include <sys/epoll.h>
#include <functional>

class Epoller: Noncopyable
{
    public:
        typedef TcpConnectCallback EpollCallback;
        Epoller(int listen_fd);
        ~Epoller();    

        void loop();
        void Epollwait();

        void setConnectCB(EpollCallback cb)
        {
            ConnectCB_ = std::move(cb);
        }
        void setMessageCB(EpollCallback cb)
        {
            MessageCB_ = std::move(cb);
        }
        void setCloseCB(EpollCallback cb)
        {
            CloseCB_ = std::move(cb);
        }
    private:
        void handleMessage(int);
        void handleConnect();

        int listen_fd_;
        int epoller_;
        bool isLoop_;

        typedef std::vector<struct epoll_event> EventEpoll;
        EventEpoll events_;
        typedef std::map<int,TcpConnectPtr> ConnectList;
        ConnectList list_;

        EpollCallback ConnectCB_;
        EpollCallback MessageCB_;
        EpollCallback CloseCB_;
        
        
        
};

#endif
