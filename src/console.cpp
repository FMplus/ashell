#include "console.h"

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

void console::execute(const std::string&file_name,const std::string&path)
{
    char*x[] = {NULL};
    std::string d = path + file_name;
    this -> put_str(d + "\n");
    execve(d.data(),x,x);
}