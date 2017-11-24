#include "Epoller.h"
#include <unistd.h>
#include <sys/epoll.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <assert.h>
#include <errno.h>

int createEpoller()
{
    int fd = ::epoll_create1(0);
    if(-1 == fd)
    {
        fprintf(stderr,"epoll_create error\n");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void addEpollfd(int listen,int fd)
{
    struct epoll_event eve;
    eve.events = EPOLLIN;
    eve.data.fd = fd;
    if(-1 == epoll_ctl(listen,EPOLL_CTL_ADD,fd,&eve))
    {
        fprintf(stderr,"addEpollfd error");
        exit(EXIT_FAILURE);
    }

}

void delEpollfd(int listen,int fd)
{
    struct epoll_event eve;
    eve.events = EPOLLIN;
    eve.data.fd = fd;
    if(-1 == epoll_ctl(listen,EPOLL_CTL_DEL,fd,&eve))
    {
        fprintf(stderr,"delEpollfd error");
        exit(EXIT_FAILURE);
    }   
}

int acceptfd(int listen)
{
    int fd = ::accept(listen,NULL,NULL);
    if(fd == -1)
    {
        fprintf(stderr,"accept error\n");
        exit(EXIT_FAILURE);
    }
    return fd;
}

int recvPeek(int fd,char *buf,int len)
{
    int num;
    do
    {
        num = ::recv(fd,buf,len,MSG_PEEK);
    
    }while(num == -1 && errno == EINTR);
    
    return num;
}

bool isCloseConnect(int fd)
{
    char buf[1024];
    int num = recvPeek(fd,buf,sizeof buf);
    if(num == -1)
    {
        fprintf(stderr,"recvPeek error\n");
        exit(EXIT_FAILURE);
    }
    return num == 0;
}

void Epoller::handleConnect()
{
    int fd = acceptfd(listen_fd_);
    addEpollfd(epoller_,fd); 
    TcpConnectPtr ptr(new TcpConnect(fd));
    std::pair<ConnectList::iterator,bool> ret;

    ptr ->setConnectCB(ConnectCB_);
    ptr ->setMessageCB(MessageCB_);

    ret = list_.insert(std::make_pair(fd,ptr));
    assert(ret.second == true);
    printf("welcome connect\n");
    (void)ret;

    ptr ->handleConnectCallback();
}

void Epoller::handleMessage(int fd)
{
    bool isClose = isCloseConnect(fd);
    ConnectList::iterator it = list_.find(fd);
    assert(it != list_.end());

    if(isClose)
    {
        delEpollfd(epoller_,fd);
        it->second->handleCloseCallback();
        list_.erase(it);
    }
    else
    {
        it->second->handleMessageCallback();
    }
}

Epoller::Epoller(int listen_fd)
:listen_fd_(listen_fd)
,epoller_(createEpoller())
,isLoop_(false)
,events_(1024)
{
    addEpollfd(epoller_,listen_fd_);    
}

Epoller::~Epoller()
{
    ::close(epoller_);
}

void Epoller::loop()
{
    isLoop_ = true;
    while(isLoop_)
    {
        Epollwait();
    }
}

void Epoller::Epollwait()
{
    int ready;
    do
    {
        ready = ::epoll_wait(epoller_,&*events_.begin(),events_.size(),5000);

    }while(ready == -1 && errno == EINTR);
    if(ready == -1)
    {
        fprintf(stderr ,"epoll_wait error\n");
        exit(EXIT_FAILURE);
    }
    if(ready == 0)
    {
        printf("epoll time_out\n");
    }
    else
    {
        if(ready == static_cast<int>(events_.size()))
        {
            events_.resize(events_.size()*2);
        }
        for(int i=0;i!=ready;++i)
        {
            if(events_[i].data.fd == listen_fd_)
            {
                if(events_[i].events & EPOLLIN)
                    handleConnect();
            }
            else if(events_[i].events & EPOLLIN)
            {    
                handleMessage(events_[i].data.fd);
        
            }
        }

    }
}



