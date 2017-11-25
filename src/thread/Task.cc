#include "Task.h"
#include "countBytes.h"
#include <iostream>
#include <set>
#include <algorithm>


Task::Task(std::string str,int fd,Diction & dic)
:str_(str)
,sockfd_(fd)
,dic_(dic)
{}


void Task::execute(Cache & cahe)
{
/*
    std::string ans = cache.queue_cache(str_);
    if(ans != std::string())
    {
        write(ans); 
    }
    else{
        query_idx_table();
        response(cache);
    }
*/
}
/*
void Task::query_idx_table()
{
    std::string ch;
    auto idx_table = dic_.word_map_index();
    for(std::size_t idx = 0 ;idx < str_.size();++idx)
    {
        size_t num = countBytes(str_[idx]);
        ch = str_.substr(idx,num);
        idx += num -1;
        if(idx_table.count(ch))
        {
            statistic(idx_table[ch]);   
        }
    }
}

void Task::statistic(std::set<int> & list)
{
    auto dic = dic_.get_dic();
    auto it = list.begin();
    for(;it != list.end();++it)
    {
        std::string word = dic[*it].first;
        int dist = distance(word);
        if(dist < 3)
        {
            Myresult ans;
            ans.word_ = word;
            ans.freq_ = dic[*it].second;
            ans.dist_ = dist; 
            que_res_.push(ans);
        }
    }
}

size_t distance(std::string & word)
{
    size_t alen = str_.length();
    size_t blen = word.length(); 
    size_t dist[alen+1][blen+1] = 0;
    for(int i=0;i<=alen;++i)
    {
        dist[i][0] = i;
    }
    for(int j=0;j<=blen;++j)
    {
        dist[0][j] = j;
    }
    for(int i=1,ai=0;i<=alen;++i,++ai)
    {
        int alen = countBytes(str_[ai]);
        std::string astr = str_.substr(ai,num);
        ai += alen -1;
        for(int j=1,bj=0;j<=blen;++j,++bj)
        {
            int jlen = countBytes(word[bj]);
            std::string bstr = word.substr(bj,jlen);
            bj += jlen -1;
            if(astr == bstr)
            {
                dist[i][j] = dist[i-1][j-1];
            }else{
                dist[i][j] = min(min(dist[i-1][j],dist[i][j-1]),dist[i-1][j-1]+1);
            }
        }
    }
    return dist[alen][blen];
}

*/
