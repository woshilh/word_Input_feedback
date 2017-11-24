#ifndef MYTIMER_H
#define MYTIMER_H

#include "Noncopyable.h"
#include "Timer.h"
#include "TimerThread.h"
#include <functional>

class MyTimer : Noncopyable
{
    typedef std::function<void ()> Callback;
    public:
        MyTimer(int val,int interval,Callback cb);

        void start();
        void stop();
    private:
        Timer timer_;
        TimerThread thread_;
};

#endif
