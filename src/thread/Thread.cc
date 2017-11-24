#include "Thread.h"
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>

Thread::Thread(ThreadCallback call,Cache & cache)
:pthId_(0)
,isRuning_(false)
,call_(std::move(call))
,cache_(cache)
{
    std::cout << " create success" << std::endl;
}

Thread::~Thread()
{
    if(isRuning_)
        pthread_detach(pthId_);
}

void Thread::start()
{
    pthread_create(&pthId_,NULL,ThreadFunction,this);
    isRuning_ = true;
}

void Thread::join()
{
    assert(isRuning_);
    pthread_join(pthId_,NULL);
    isRuning_ = false;
}

void * Thread::ThreadFunction(void * arg)
{
    Thread * tab = static_cast<Thread *>(arg);
    tab->call_(tab->cache_);
    return NULL;
}

