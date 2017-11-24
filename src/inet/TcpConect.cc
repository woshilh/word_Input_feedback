#include "TcpConnect.h"

TcpConnect::TcpConnect(int fd)
:sock_(fd)
,sockIO_(fd)
{}

void TcpConnect::handleConnectCallback()
{
    if(connectCallback_)
    {
        connectCallback_(shared_from_this());
    }
}

void TcpConnect::handleMessageCallback()
{
    if(messageCallback_)
    {
        messageCallback_(shared_from_this());
    }
}

void TcpConnect::handleCloseCallback()
{
    if(closeCallback_)
    {
        closeCallback_(shared_from_this());
    }
}

const char* TcpConnect::receive()
{
    char buf[1024];
    int len = sizeof (buf);
    sockIO_.read(buf,len);
    return buf;
}

void TcpConnect::send(const std::string & str)
{
    int len = str.length();
    sockIO_.send(str.c_str(),len);
}
