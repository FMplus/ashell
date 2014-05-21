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

#define IS_SSEQ   257
#define IS_APEND  258
#define IS_END    259
#define MODE_SCRIPT     0
#define MODE_INTER      1
#define MODE_STDOUT_CLOSE   (0<<1)
#define MODE_STDOUT_OPEN    (1<<1)
#define MODE_STDERR_CLOSE   (0<<2)
#define MODE_STDERR_OPEN    (1<<2)

class parser
{
public:
    typedef unsigned int mode_t;
public:
    parser(shl_io_api*iom,runtime*rt,environment*env)
    :iom(iom),rt(rt),env(env),peek(' '),
    mode(MODE_INTER|MODE_STDOUT_OPEN|MODE_STDERR_OPEN)
    {}

    void do_parse();//parser
    void set_mode(const mode_t mode);
    mode_t get_mode();
private:


    int skip_space(const std::string&s,const int n);
    int scan();//lexer
    void read();//lexer
    void move();//lexer
    char read_move();//lexer

    int input(execute_list* elist);
    int command(execute_list* elist);
    //exe_info* pushpath();
    //int make_einfo(exe_info *einfo,execute_list* elist);
    void change_dir(const std::string&path);
    void analysis(execute_list* elist);
    void put_str(const std::string&str){
        if(mode & MODE_STDOUT_OPEN)
            iom -> put_str(str);
    }
    void put_error(const std::string&str){
        if(mode & MODE_STDERR_OPEN)
            iom -> put_error(str);
    }

private:
    std::string look;

    shl_io_api*     iom;
    runtime*        rt;
    environment*    env;
    char            peek;
    int             mode;
};

#endif //PAESER
