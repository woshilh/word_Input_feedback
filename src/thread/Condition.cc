#include "Condition.h"
#include "MutexLock.h"
#include <assert.h>

Condition::Condition(MutexLock & mutex)
    :mutex_(mutex)
{
    pthread_cond_init(&cond_,NULL);
}

Condition::~Condition()
{
    pthread_cond_destroy(&cond_);
}

void Condition::wait()
{
    assert(mutex_.isLock());
    pthread_cond_wait(&cond_,mutex_.getMutex());
    mutex_.restoreStatus();
}

void Condition::notify()
{
    pthread_cond_signal(&cond_);
}

void Condition::broadcast()
{
    pthread_cond_broadcast(&cond_);
}
