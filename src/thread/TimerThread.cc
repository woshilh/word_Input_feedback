#include "TimerThread.h"

TimerThread::TimerThread(Callback cb)
:cb_(cb)
,isRunning_(false)
,pth_(0)
{}

TimerThread::~TimerThread()
{
    if(isRunning_)
        ::pthread_detach(pth_);
}

void TimerThread::start()
{
    if(-1 ==::pthread_create(&pth_,NULL,&TimerThread::Threadfunc,this))
    {
        printf("pthread_create error\n");
        exit(EXIT_FAILURE);
    }
    isRunning_ = true;
}

void TimerThread::join()
{
    ::pthread_join(pth_,NULL);
    isRunning_ = false;
}

void * TimerThread::Threadfunc(void * arg)
{
    TimerThread * ptr = static_cast<TimerThread *>(arg);
    if(ptr -> cb_)
        ptr ->cb_();
}
