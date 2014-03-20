#include "console.h"
#include<unistd.h>
#include <fcntl.h>

std::string console::get_line()
{
    std::string tmp;
    std::getline(std::cin,tmp,'\n');
    return tmp;
}

char console::get_char()
{
    return getchar();
}

void console::put_char(const char c)
{
     std::cout<<c;
}

void console::put_str(const std::string&s)
{
    std::cout<<s;
}

void console::execute(const std::string&file_name,const std::string&path)//在执行前要看是否存在
{
    char*x[] = {NULL};
    std::string d = path + file_name;
    if ( access(d.c_str(),X_OK) == -1 )
    {
        put_error("erro: "+file_name+" can not execute!");
        return;
    }
    //else
    this -> put_str(d + "\n");
    execve(d.data(),x,x);
}

void console::put_error(const std::string&s)
{
    std::cerr<<s<<std::endl;
}
