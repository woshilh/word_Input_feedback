#ifndef THREAD_H
#define THREAD_H

#include "Noncopyable.h"
#include "Cache.h"
#include <pthread.h>
#include <functional>


class Thread : Noncopyable
{
    public:
        typedef std::function<void (Cache &)> ThreadCallback;
        explicit Thread(ThreadCallback,Cache &);
        ~Thread();
        
        void start();
        void join();
    
    private:
        static void *ThreadFunction(void *);
    private:
        pthread_t pthId_;
        ThreadCallback call_;
        bool isRuning_;
        Cache cache_;
};

#endif

