#include "MutexLock.h"
#include <assert.h>


MutexLock::MutexLock():islock_(false)
{
    pthread_mutex_init(&mutex_,NULL);
}

MutexLock::~MutexLock()
{
    assert(!isLock());
    pthread_mutex_destroy(&mutex_);
}

void MutexLock::lock()
{
    islock_=true;
    pthread_mutex_lock(&mutex_);
}

void MutexLock::unlock()
{
    pthread_mutex_unlock(&mutex_);
    islock_ = false;
}


