#ifndef PARSER
#define PAESER

#include<iostream>
#include<string>
#include<dirent.h>
#include<unistd.h>
#include<sys/wait.h>

#include "shl_io_api.h"
#include "dir_list.h"
#define IS_SSEQ 257

class parser
{
public:
    parser(shl_io_api*iom,runtime*rt)
    :iom(iom),rt(rt)
    {}

    int skip_space(const std::string&s,const int n);
    int scan();
    void do_parse();
    void list_dir();
    void change_dir(const std::string&path);

private:
    std::string line;
    std::string look;

    shl_io_api*iom;
    runtime*   rt;
    class dir_list dlst;
};

#endif //PAESER
