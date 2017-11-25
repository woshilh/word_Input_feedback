#ifndef COUNT_BYTES_H
#define COUNT_BYTES_H

size_t countBytes(const char ch)
{
    size_t nBytes = 0;
    if(ch &(1 << 7))
    {//对中文进行处理-utf8编码 
        if((ch & 0xF0) == 0xC0 || (ch & 0xF0) == 0xD0)
        {
            nBytes += 2;
        }
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

#endif
