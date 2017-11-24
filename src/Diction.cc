#include "Diction.h"

Diction::pInstance_ = NULL;

Diction * Diction::createInstance(const char *filepath1,const char *filepath2)
{
    if(NULL == pInstance_)
    {
        pInstance_ = new Diction(filepath1,filepath2); 
    }
    return pInstance_;
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
