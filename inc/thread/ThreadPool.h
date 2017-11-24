#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "Thread.h"
#include "MutexLock.h"
#include "Condition.h"
#include "Task.h"
#include "Cache.h"
#include <vector>
#include <memory>
#include <queue>

class ThreadPool : Noncopyable
{
    public:
        ThreadPool(size_t threadNum ,size_t qsize,Cache &);
        
        void start();
        Task getTask();
        void addTask(Task task);
        
        void threadFunction(Cache &);
    private:
        size_t threadNum_;
        size_t qSize_;

        MutexLock mutex_;
        Condition empty_;
        Condition full_;
        Cache cache_;

        std::vector<std::unique_ptr<Thread> > threads_;
        std::queue<Task> Tqueue_;
        
        bool isExit_;
        
};

#endif
