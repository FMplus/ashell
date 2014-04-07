#ifndef PARSER
#define PAESER

#include<iostream>
#include<string>
#include<dirent.h>
#include<unistd.h>
#include<sys/wait.h>
#include<cstdlib>

#include "shl_io_api.h"
#include "exe_utils.h"
#include "env.h"
#include "pipex.h"
#include"pipe_api.h"

#define IS_SSEQ 257

class parser
{
public:
    parser(shl_io_api*iom,runtime*rt,environment*env)
    :iom(iom),rt(rt),env(env),peek(' ')
    {}

    int skip_space(const std::string&s,const int n);
    int scan();//lexer
    void read();//lexer
    void move();//lexer
    char read_move();//lexer
    void do_parse();//parser
    exe_info* pushpath();
    int make_einfo(exe_info *einfo,execute_list* elist);
    void list_dir();
    void change_dir(const std::string&path);
    void analysis(execute_list* elist);
    void ctrlpipe(execute_list* elist,int i,pipex h);

private:
    std::string look;

    shl_io_api*     iom;
    runtime*        rt;
    environment*    env;
    char            peek;
};

#endif //PAESER
