#ifndef _FILE_IO_API_H_
#define _FILE_IO_API_H_
#include "shl_io_api.h"
#include <ifstream>
#include <string.h>
#include <string>

class file_io_api:public shl_io_api
{
    public:
    ~file_io_api(){}
    void        open_file(std::string filename);
    std::string get_line();
    char        get_char();
    void        put_char(const char c);
    void        put_str(const std::string&s);
    void        put_error(const std::string&s);
    private:
    std::ifstream file;
};

void file_io_api::open_file(std::string filename)
{
    file.open(filename,ios::out|ios::in);
}

std::string file_io_api::get_line()
{
    return file.getline();
}

char file_io_api::get_char()
{
    return file.get();
}

void file_io_api::put_char(const char c)
{
    if (file.is_open())
    {
        file.write(c,1);
    }
    else
    {
        this -> put_error("ERROR: File not open!");
    }
}

void file_io_api::put_str(const std::string&s)
{
    if (file.is_open())
    {
        file.write(s,strlen(s));
    }
    else
    {
        this -> put_error("ERROR: File not open!");
    }
}

void file_io_api::put_error(const std::string&s)
{
    std::cerr << s << std::endl;
}

file_io_api::~file_io_api()
{
    if (file.is_open())
    {
        file.close();
    }
}
