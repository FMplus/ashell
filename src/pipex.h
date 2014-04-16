#ifndef _PIPE_X_H
#define _PIPE_X_H

#include"pipe_api.h"

#include<unistd.h>
#include<fcntl.h>


struct filex:public file_basic{
    public:
    friend class redirects;
    ~filex();
    bool open(const string&file_name);
    bool write_empty(const string&file_name);
    bool write_after(const string&file_name);
    int get_fd();
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

class redirects:public redir_basic{
    public:
        redirects();
        ~redirects();
        bool redirects_open(const string&file_name);
        bool apend_open(const string&file_name);
        int write_tie(TYPE);
        int close_write();
        int close();
    private:
        filex* fd;
};

#endif //_PIPE_X_H
