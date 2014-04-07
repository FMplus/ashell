#ifndef _PIPE_API_H
#define _PIPE_API_H

#include<string>

struct file_basic{
    typedef std::string string;
    virtual ~file_basic(){}
    virtual bool open(const string&) = 0;
    virtual bool is_open()const = 0;
    virtual void close() = 0;
};

enum TYPE{
    STD_IN,STD_OUT,STD_ERR,NONE
};

struct pipe_basic{
    pipe_basic()
    {}
    virtual ~pipe_basic()
    {}
    
    virtual bool is_open()const = 0;
    virtual int close_write() = 0;
    virtual int close_read() = 0;
    virtual int write_tie(TYPE) = 0;
    virtual int read_tie(TYPE) = 0;
    //virtual int write_tie_file(file_basic&) = 0;
    //virtual int read_tie_file(file_basic&) = 0;
};//struct pipe_basic

#endif //_PIPE_API_H
