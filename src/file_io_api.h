#ifndef _FILE_IO_API_H_
#define _FILE_IO_API_H_
#include "shl_io_api.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#define SIZE_OF_BUFFER 256

class file_io_api:public shl_io_api
{
    public:
    ~file_io_api();
    void        open_file(std::string filename);
    std::string get_line();
    char        get_char();
    bool        is_end();
    void        put_char(const char c);
    void        put_str(const std::string&s);
    void        put_error(const std::string&s);
    private:
    std::fstream file;
    //char buffer[SIZE_OF_BUFFER];
};

bool file_io_api::is_end()
{
    if (file.eof())
    {
        return true;
    }
    return false;
}//is_end

void file_io_api::open_file(std::string filename)
{
    file.open(filename.c_str(),std::ios::out|std::ios::in);
    if (!file.is_open())
    {
        this -> put_error("ERROR: Open " + filename + " fail!");
    }
}//open_file

std::string file_io_api::get_line()
{
    std::string str;
    if (!file.eof())
    {
        std::getline(file,str,'\n');
    }
    return str;
}//get_line

char file_io_api::get_char()
{
    if (!file.eof())
        return file.get();
}//get_char

void file_io_api::put_char(const char c)
{
    std::cout<<c;
}//put_char

void file_io_api::put_str(const std::string&s)
{
    std::cout<<s<<std::endl;
    //this -> put_error("ERROR: File not open!");
}//put_str

void file_io_api::put_error(const std::string&s)
{
    std::cerr << s << std::endl;
}//put_error

file_io_api::~file_io_api()
{
    if (file.is_open())
    {
        file.close();
    }
}

#endif
