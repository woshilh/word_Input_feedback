#ifndef SOCKETIO_H
#define SOCKETIO_H

#include "Noncopyable.h"

class SocketIO: Noncopyable
{
    public:
        SocketIO(int fd);
        ~SocketIO(){}

        int read(char*,int);
        int readn(char*,int);
        void send(const char *,int);
    private:
        int recv_peek(char*);
    private:
        int fd_;
};
#endif
