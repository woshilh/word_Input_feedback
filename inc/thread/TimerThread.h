#ifndef TIMERTHREAD_H
#define TIMERTHREAD_H

#include "Noncopyable.h"
#include <functional>
#include <pthread.h>

class TimerThread : Noncopyable
{
    typedef std::function<void () > Callback;
    public:
        TimerThread(Callback);
        ~TimerThread();
        void start();
        void join();
    private:
        static void *Threadfunc(void *arg);

    private:
        pthread_t pth_;
        bool isRunning_;
        Callback cb_;
};

#endif
