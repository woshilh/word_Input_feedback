#include "Diction.h"
#include "countBytes.h"
#include <iostream>

Diction *Diction::pInstance_ = NULL;

Diction * Diction::createInstance(const char *filepath1,const char *filepath2)
{
    if(NULL == pInstance_)
    {
        pInstance_ = new Diction(filepath1,filepath2); 
    }
    return pInstance_;
}

void Diction::show_dic()
{
    for(size_t idx=0;idx != dic_.size();++idx)
    {
        std::cout << dic_[idx].first
            << " -->> " << dic_[idx].second
            << std::endl;
    }
}

void Diction::show_index()
{

}

void Diction::read_from(const char* filepath)
{
    std::ifstream ifs(filepath);
    if(!ifs)
    {
        printf("ifstream error \n");
        exit(EXIT_FAILURE);
    }
    std::string line;
    while(::getline(ifs,line))
    {
        std::stringstream in(line);
        std::string key;
        int val;
        in >> key >> val;
        dic_.push_back(std::make_pair(key,val));
    }
    ifs.close();
}

void Diction::create_index(int idx)
{
    std::string word = dic_[idx].first;
    for(size_t idx = 0;idx < word.size();++idx)
    {
        size_t nbyte = countBytes(const char ch);
        std::string key = word.substr(idx,nbyte);
        idx += nbyte - 1;
        index_tab_[key].inster(idx);
    }
}
Diction::Diction(const char *filepath1,const char *filepath2)
{
    read_from(filepath1);
    read_from(filepath2);

    for(size_t idx = 0;idx != dic_.size();++idx)
    {
        create_index(idx);
    }
}
