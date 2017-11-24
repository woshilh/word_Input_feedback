#include <algorithm>
#include <iostream>
#include <string>

size_t countBytes(const char ch) 
{
   size_t nBytes = 0;
   if(ch &(1 << 7)) 
   {//对中文进行处理-utf8编码
       if((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0)   //  1111 0000
           {                                                // &11xx xxxx
                                        nBytes += 2;                                 //  1100 0000  
                                    }                                                //  1101 0000
                            else if((ch & 0xF0) == 0xE0)
                            {   
                                        nBytes += 3;
                                    }   
                            else if((ch & 0xF0) == 0xF0)
                            {   
                                        nBytes += 4;
                                    }   
                            else if((ch & 0xFF) == 0xF8)
                            {   
                                        nBytes += 5;
                                    }   
                            else if((ch & 0xFF) == 0xFE)
                            {   
                                        nBytes += 6;
                                    }   
                        }   
                else
                        {//1字节编码或英文
                                nBytes += 1;        
                            }   
                    return nBytes;

}

size_t Distance(const std::string & str_,const std::string & word)
{
    size_t alen = str_.length();
    size_t blen = word.length(); 
    size_t dist[alen+1][blen+1] = {0};
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
        std::string astr = str_.substr(ai,alen);
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
               dist[i][j] = std::min(std::min(dist[i-1][j],dist[i][j-1]),dist[i-1][j-1]+1);
            }
        }
    }
    return dist[alen][blen];
}


int main()
{
    std::string s1 = "明";
    std::string s2 = "今";
    size_t len = Distance(s1,s2);
    std::cout << len << std::endl;
    return 0;
}
