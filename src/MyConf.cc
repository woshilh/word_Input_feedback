#include "MyConf.h"
#include <iostream>
#include <fstream>
#include <sstream>

MyConf::MyConf(std::string & path)
    :filepath_(path)
{}

bool MyConf::init()
{
    std::ifstream ifs(filepath_.c_str());
    if(!ifs)
    {
        std::cout << "open filepath error" << std::endl;
        return false;
    }
    std::string line;
    while(getline(ifs,line))
    {
        std::istringstream ins(line);
        std::string key,value;
        ins >> key >> value;
        map_.insert(make_pair(key,value));
    }
    ifs.close();
    return true;
}

void MyConf::show()
{
    std::map<std::string,std::string>::const_iterator it = map_.begin();
    for(;it!=map_.end();++it)
    {
        std::cout << it->first << " : " << it->second << std::endl;
    }
}
