#ifndef TASK_H
#define TASK_H

#include "Cache.h"
#include "Diction.h"
#include <string>


class Task
{
   public:
        Task(std::string str,int fd,Diction &dic);
        
        void execute(Cache &);
   private:
        std::string str_;
        int sockfd_;
        Diction dic_;
        
};

#endif
