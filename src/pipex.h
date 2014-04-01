#ifndef _PIPE_X_H
#define _PIPE_X_H

#include"pipe_api.h"

#include<unistd.h>
#include<fcntl.h>


struct filex:public file_basic{
    public:    
    friend class pipex;
    ~filex();
    bool open(const string&file_name);
    bool is_open()const;
    void close();
    private:
    int file_id;
};//struct filex

class pipex:public pipe_basic{
    public:
    pipex();
    ~pipex();
    public:
    bool is_open()const;
    int close_write();
    int close_read();
    int write_tie(TYPE);
    int read_tie(TYPE);
    //int write_tie_file(file_basic&file);
    //int read_tie_file(file_basic&file);
    private:
    int fd[2];
};//class pipex

#endif //_PIPE_X_H
