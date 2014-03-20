#include "parser.h"
#include "list_inode.h"
#include "console.h"


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
        iom -> put_str( dlst.combine() + "#");
        switch(this -> scan()){
        case '\0':
        case '\n':
            continue;
        case IS_SSEQ:
            if(look == "cd"){
                int i = this->scan();
                if(i!= '\0'&&i != '\n')
                    buf = look;
                line.clear();
                this -> change_dir(buf);
            }else if(look == "dir"){
                this -> list_dir();
                line.clear();
            }else if(look == "exit"){
                return;
            }else{
                pid_t pid = fork();
                if(pid == 0){
                    iom -> put_str("It is in child!!!\n");
                    rt-> execute(look,dlst.combine());
                }else if(pid > 0){
                    iom -> put_str("It is in father!!\n");
                    wait(NULL);
                }else{
                    iom -> put_str("Fork wrong!!!\n");
                }

            }
        }
    }
}

void parser::list_dir()//dir
{
    std::string tmp = dlst.combine();
    DIR*dir = opendir(tmp.data());
    struct dirent* ent = NULL;
    while(NULL != (ent=readdir(dir))){
        iom -> put_str(std::string(ent -> d_name) + "\n");
    }
    closedir(dir);
}

void parser::change_dir(const std::string&path)
{
    //'path' is the dir_name to change , dlst.combine() is the current path;
    std::string curpath = dlst.combine() + path;
    if ( opendir(curpath.c_str()) == NULL )
    {
        class console s;
        s.put_error("erro: can not find "+path);
        return;
    }
    //else
    std::string tmp,buf;
    int i = 0;
    if(path[0] == '/'){
        dlst.go_root();
        i++;
    }
    while(i < path.length()){
        for(;path[i] != '/'&&path[i] != '\0';i++){
            buf += path[i];
        }
        if(buf.empty())
            break;
        dlst.push(buf);
        i++;
        buf = "";
    }
}//change_dir
