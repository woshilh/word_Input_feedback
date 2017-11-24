#include <string>
#include <map>

class MyConf
{
public:
    MyConf(std::string & str);

    bool init();

    std::map<std::string,std::string> & getMap()
    {
        return map_;
    }
    
    void show();

private:
    std::string filepath_;
    std::map<std::string,std::string> map_;
};

