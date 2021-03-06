#include "parser.h"
#include "pipex.h"
#include"pipe_api.h"
#include<semaphore.h>

int parser::skip_space(const std::string&s,const int n)
{
    int i = n;
    while(s[i] == ' '||s[i] == '\t'){
        i++;
    }
    return i;
}

void parser::move()
{
    this -> read();
}

void parser::read()
{
    peek = iom -> get_char();
}

char parser::read_move()
{
    char c = peek;
    this -> move();
    return c;
}

int parser::scan()
{
    static int i = 0;
    char c;
    look.clear();

    l2:
    switch(this -> peek){
    case '>':
        look += this -> read_move();
        if (peek == '>')
        {
            look += this -> read_move();
            return IS_APEND;//additional rediection
        }
        else
            return '>';
    case '|':
        look += this -> read_move();
        return '|';
    case '\0':case '\n':
        this -> peek = ' ';
        return '\n';
    case ' ':case '\t':
        while(peek == ' '|| peek == '\t')
            this -> move();
        goto l2;
    case '\"':case '\'':
        c = this -> read_move();
        /*
         * considing that '\n' is the begining of a new line
         */

        while(peek != '\0' && peek != c){
            if(peek == '\\'){
                this -> move();
                if(peek == '\"'||peek == '\'')
                    look += this -> read_move();
                else
                    look += '\\';
            }
            else
                look += this -> read_move();
        }
        this -> move();
        /*
         * If the next peek is ' ','|','\n' or '\t' we should return because it is a block.
         * Or we should conitune the scan work.
         */
        if(peek != '\n' && peek != ' ' && peek != '\t' && peek != '|' && peek != '>')
            goto l2;
        return IS_SSEQ;

    default:
        do
            look += read_move();
        while(peek != '\0' && peek != '\n' && peek != ' '
           && peek != '\t' && peek != '\"' && peek != '\''&& peek != '|' && peek != '>');
        if(peek == '\'' || peek == '\"')
            goto l2;
        return IS_SSEQ;
    }
}

void parser::do_parse()
{
    std::string buf;
    para_list   args;
    while(true){
        iom -> put_str( env -> where() + "#");
        switch(this -> scan()){
        case '\0':
        case '\n':
            continue;
        case IS_SSEQ:
            if(look == "cd"){
                int i = this->scan();
                if(i!= '\0'&&i != '\n')
                    buf = look;
                while(i!= '\0' && i != '\n')
                    i = this -> scan();
                this -> change_dir(buf);
            }else if(look == "exit"){
                return;
            }else{
                execute_list* elist = new execute_list;

                if (this -> input(elist))
                    break;

                this -> analysis(elist);
            }break;
        default:
            iom -> put_error("ERROR: UNKNOWN ERROR!\n");
            break;
        }
    }
}

int parser::input(execute_list* elist)
{
    int x = this -> command(elist);
    switch (x)
    {
    case 0:
        return 0;break;
    case '|':
        this -> input(elist);break;
    case '>':
    case IS_APEND:{
        if ( this -> scan() == IS_SSEQ)
        {
            elist -> set_pathname(look);
            if (this -> scan() == '\n')
                return 0;
            else
            {
                iom -> put_error("ERROR: DOES NOT SUPPORT THIS COMMAND!\n");
                return 1;
            }
        }
        else
        {
            iom -> put_error("ERROR: FILENAME FORMAT ERROR!\n");
            return 1;
        }
        }break;
    default:
        iom -> put_error("ERROR: UNKNOWN ERROR!\n");
        return 1;break;
    }
}

int parser::command(execute_list* elist)
{
    if (look == "")
        return 1;
    exe_info* einfo = new exe_info;
    einfo -> set_pathname(look);
    while(true)
    {
        switch(this -> scan())
        {
            case '\n':
            case '\0':
                elist -> push_exenode(einfo);
                return 0;break;
            case '|':
                elist -> push_exenode(einfo);
                this -> scan();
                return '|';break;
            case '>'://rediection
                elist -> push_exenode(einfo);
                elist -> set_redirected(true);
                return '>';break;
            case IS_APEND://apend
                elist -> push_exenode(einfo);
                elist -> set_apend(true);
                return IS_APEND;break;
            default:
                einfo -> push_arg(look);
                break;
        }
    }
}

void parser::list_dir()
{
    std::string cwd = env -> where();
    DIR*dir = opendir(cwd.data());
    struct dirent* ent = NULL;
    while(NULL != (ent=readdir(dir))){
        iom -> put_str(std::string(ent -> d_name) + "\n");
    }
    closedir(dir);
}

void parser::change_dir(const std::string&path)
{
    int flag;
    if((flag=env -> change_dir(path))==CH_OK){
        //
    }else if(flag == DIR_NOT_EXISTED){
        iom -> put_error("NOT EXIST!\n");
    }else{
        iom -> put_error("ERROR:UNKNOW ERROR!\n");
    }
}

void parser::analysis(execute_list* elist)//analysis the option to execute
{
    int SIZE = elist -> size();
    if (SIZE < 1)
    {
        iom -> put_error("ERROR:NOTHING TO EXECUTE!\n");
        return;
    }
    else
    {
        int i = 0;
        pipex* pipe_1 = NULL;

        pipex* pipe_2 = NULL;
        if(SIZE > 1)
            pipe_2 = new pipex;
        do{
            if (fork())//father
            {
                if (pipe_1 != NULL){
                    pipe_1 -> close_read();
                    delete pipe_1;
                }
                if( i < SIZE ){
                    if(pipe_2 != NULL)
                        pipe_2 -> close_write();
                    pipe_1 = pipe_2;
                    pipe_2 = new pipex;
                }
                else
                {
                    if (pipe_2 != NULL)//make pipe_2 null while i < (size-1)
                    {
                        delete pipe_2;
                        pipe_2 = NULL;
                    }
                }
            }
            else//child
            {
                if (pipe_1 != NULL)//stdin
                {
                    pipe_1 -> close_write();
                    pipe_1 -> read_tie(STD_IN);
                }
                if (pipe_2 != NULL && ((i+1) < SIZE))//stdout
                {
                    pipe_2 -> close_read();
                    pipe_2 -> write_tie(STD_OUT);
                }
                if ( (i+1) == SIZE && (elist->is_redirected() || elist->is_apend()) )
                {
                    redirects* redi = new redirects;
                    if (elist->is_redirected())
                    {
                        redi -> redirects_open(elist -> get_pathname());
                    }
                    else if (elist->is_apend())
                    {
                        redi -> apend_open(elist -> get_pathname());
                    }
                    redi -> write_tie(STD_OUT);
                    rt -> execute(elist -> at(i) -> get_path(),elist -> at(i) -> args);
                    redi -> close_write();
                    delete redi;
                }
                else
                    rt -> execute(elist -> at(i) -> get_path(),elist -> at(i) -> args);

                exit(1);
            }
            i++;
        }while( i < SIZE);

        if (pipe_1 != NULL)
            delete pipe_1;
        if (pipe_2 != NULL)
            delete pipe_2;

        for(int i = 0;i < SIZE;i++) wait(NULL);
    }
}
