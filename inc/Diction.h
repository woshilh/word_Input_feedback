#ifndef DICTION_H
#define DICTION_H

#include <string>
#include <map>
#include <set>
#include <utility>
#include <vector>


class Diction
{
    public:
        static Diction * createInstance (const char *,const char *);
        std::vector<std::pair<std::string,int> > & get_dict();
        std::map<std::string,std::set<int> >  & get_index_tab();
   
        void show_dic();
        void show_index();
    private:
        Diction(const char * ,const char *);
        void read_from(const char *);
        void create_index(int);

    private:
        static Diction * pInstance_;
        std::map<std::string,std::set<int> > index_tab_;
        std::vector<std::pair<std::string,int> > dic_;
};
#endif
