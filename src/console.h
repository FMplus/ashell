#ifndef CONSOLE
#define CONSOLE

#include<iostream>
#include<string>
#include<list>
#include<stdio.h>

#include<unistd.h>

#include "shl_io_api.h"
#include "envx.h"

class console:public shl_io_api,public runtime,public envx
{
    public:
          std::string get_line();
          char get_char();
          void put_char(const char c);
          void put_str(const std::string&s);
          void execute(const std::string&file_name,const std::string&path);
          void put_error(const std::string&s);
    private:

};



#endif //CONSOLE
