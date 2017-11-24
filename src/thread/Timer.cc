#include <Timer.h>
#include <sys/timerfd.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <poll.h>

int createTimer()
{
    int fd = ::timerfd_create(CLOCK_REALTIME,0);
    if(fd == -1)
    {
        perror("timerfd_create error\n");
        exit(EXIT_FAILURE);
    }
    return fd;
}

void setTimerfd(int timer,int val,int interval)
{
    struct itimerspec it;
    it.it_value.tv_sec = val;
    it.it_interval.tv_sec = interval;
    if(-1 == ::timerfd_settime(timer,0,&it,NULL))
    {
        perror("setTimerfd error\n");
        exit(EXIT_FAILURE);
    }
}

void stopTimer(int timer)
{
    setTimerfd(timer,0,0);
}

void readTimerfd(int fd)
{
    uint64_t ret;
    if(-1 == ::read(fd,&ret,sizeof ret))
    {
        printf("readTimerfd error\n");
        exit(EXIT_FAILURE);
    }
}
Timer::Timer(int val,int interval,Callback cb)
    :val_(val)
     ,interval_(interval)
     ,timer_(createTimer())
     ,status_(false)
     ,cb_(cb)
{}

Timer::~Timer()
{
    if(status_)
    {
        stopTimer(timer_);
        ::close(timer_);
    }
}

void Timer::stop()
{
    stopTimer(timer_);
    status_ = false;
}

void Timer::start()
{
    setTimerfd(timer_,val_,interval_);
    status_ = true;
    
    struct pollfd pfd;
    pfd.fd = timer_;
    pfd.events = POLLIN;
    
    while(status_)
    {
        int ret = ::poll(&pfd,1,5000);
        if(ret == -1 && errno == EINTR)
            continue;
        else if(ret == 0)
        {
            printf("poll timeout\n");
            continue;
        }
        else if(ret == -1)
        {
            printf("poll error\n");
            exit(EXIT_FAILURE);
        }
         else if(pfd.revents == POLLIN)
        {
            readTimerfd(timer_);
            if(cb_)
                cb_();
        }
            
    }
}




