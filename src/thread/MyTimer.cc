#include "MyTimer.h"

MyTimer::MyTimer(int val,int interval,Callback cb)
:timer_(val,interval,cb)
,thread_(std::bind(&Timer::start,&timer_))
{}


void MyTimer::start()
{
    thread_.start();
}

void MyTimer::stop()
{
    timer_.stop();
    thread_.join();
}

