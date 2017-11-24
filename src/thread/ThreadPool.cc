#include "ThreadPool.h"
#include "Thread.h"
#include "Condition.h"
#include "MutexLock.h"
#include "Task.h"
#include <unistd.h>
#include <iostream>

ThreadPool::ThreadPool(size_t threadNum, size_t qsize,Cache &cache)
:threadNum_(threadNum)
,qSize_(qsize)
,isExit_(false)
,empty_(mutex_)
,full_(mutex_)
,cache_(cache)
{
    std::cout << "ThreadPool beginning" << std::endl;
}

void ThreadPool::start()
{
    for(int i=0;i!=threadNum_;++i )
    {
        threads_.push_back(std::unique_ptr<Thread>
                (new Thread(std::bind(&ThreadPool::threadFunction,this,std::placeholders::_1),cache_)));
    }
    for(int i=0;i!=threadNum_;++i)
    {
        threads_[i]->start();
    }
}

void ThreadPool::addTask(Task task)
{
   AutoMutexLock mutex(mutex_);
   while(Tqueue_.size() >=  qSize_ )
       empty_.wait();
   Tqueue_.push(task);
   full_.notify();
}

Task ThreadPool::getTask()
{
    AutoMutexLock mutex(mutex_);
    while(Tqueue_.empty())
        full_.wait();
    Task t = Tqueue_.front();
    Tqueue_.pop();
    empty_.notify();
    return t;
}

void ThreadPool::threadFunction(Cache & cache)
{
    while(!isExit_)
    {
        Task task(getTask());
        task.execute(cache);
        sleep(5);
    }
}

/*

int main()
{
    ThreadPool pool(3,5);
    pool.start();
    while(1)
    {
        Task t;
        sleep(1);
        pool.addTask(t);
    }
    return 0;
}
*/
