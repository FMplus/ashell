#include "parser.h"

int parser::skip_space(const std::string&s,const int n)
{
    int i = n;
    while(s[i] == ' '||s[i] == '\t'){
        i++;
    }
    return i;
}

int parser::scan()
{
    static int i = 0;
    look.clear();
    if(i >= line.length()){
         i = 0;
         line =  iom -> get_line();
    }
    i = skip_space(line,i);
    switch(line[i]){
    case '\0':
    case '\n':
        return line[i++];
    default:
       while(line[i] != '\0'&&line[i] != ' '
            &&line[i] != '\n'&&line[i] != '\t'){
        look += line[i];
        i++;
       }

       return IS_SSEQ;
    }
}

void parser::do_parse()
{
    std::string buf;
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
                line.clear();
                this -> change_dir(buf);
            //}else if(look == "dir"){
              //  this -> list_dir();
                //line.clear();
            }else if(look == "exit"){
                return;
            }else{
                pid_t pid = rt -> fork();
                //TODO Parase the paraments.
                if(pid == 0){
                   // iom -> put_str("It is in child!!!\n");
                    rt -> execute(look,"./");
                    rt -> exit();
                }else if(pid > 0){
                   // iom -> put_str("It is in father!!\n");
                    wait(NULL);
                }else{
                    iom -> put_str("Fork wrong!!!\n");
                }

            }
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
