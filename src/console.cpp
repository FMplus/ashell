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
    char*args[] = {"/bin/ls",NULL};
    char*envp[] = {"PATH=/bin/",NULL};
    //chdir(path.data());
    std::string d = std::string("/bin/")+file_name;
    //this -> put_str(d + "\n");
    //this -> put_str(path + "\n");
    //this -> put_str(file_name + "\n");
    execve(d.data(),args,envp);
    this -> put_error(d + " executed not well,What happened???\n");
    ::exit(0);
}


void console::put_error(const std::string&s)
{
    std::cerr<<s;
}

void console::exit()
{
    ::exit(0);
}

int console::fork()
{
	return ::fork();
}
