#ifndef MUTEXLOCK_H
#define MUTEXLOCK_H

#include "Noncopyable.h"
#include <pthread.h>


class MutexLock : Noncopyable
{
    friend class Condition;
    
    public:
        MutexLock();
        ~MutexLock();

        void lock();
        void unlock();

        bool isLock(){
            return islock_;
        }

        pthread_mutex_t * getMutex()
        {
            return &mutex_;
        }

        void restoreStatus()
        {
            islock_ = true;
        }
    private:
        pthread_mutex_t mutex_;
        bool islock_;
};

class AutoMutexLock 
{
    public:
    AutoMutexLock(MutexLock & mutex)
        :lock_(mutex)
    {
        lock_.lock();
    }
    ~AutoMutexLock()
    {
        lock_.unlock();
    }
    private:
        MutexLock & lock_;
};

#endif

