#ifndef CONDITION_H
#define CONDITION_H

#include "Noncopyable.h"
#include <pthread.h>

class MutexLock;

class Condition : Noncopyable
{
    public:
        Condition(MutexLock & );
        ~Condition();

    void wait();
    void notify();
    void broadcast();
    
    private:
        MutexLock & mutex_;
        pthread_cond_t cond_;
};
    
#endif
