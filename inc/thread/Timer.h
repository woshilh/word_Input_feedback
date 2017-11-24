#ifndef TIMER_H
#define TIMER_H

#include "Noncopyable.h"
#include <functional>


class Timer:Noncopyable
{

    public:
        typedef std::function<void ()> Callback;
        Timer(int,int,Callback);
        ~Timer();

        void start();
        void stop();

    private:
        int val_;
        int timer_;
        int interval_;
        Callback cb_;
        bool status_;
};
#endif
