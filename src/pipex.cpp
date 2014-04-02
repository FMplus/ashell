#include"pipex.h"

#include<sys/types.h>
#include<sys/stat.h>


/*struct filex*/
filex::~filex()
{
    this -> close();
}

bool filex::open(const string&file_name)
{
   this -> file_id = ::open(file_name.data(),O_CREAT|O_WRONLY);
   return this -> is_open();
}

bool filex::is_open()const
{
    return (this -> file_id >= 0);
}

void filex::close()
{
    if(this -> is_open())
        ::close(file_id);
}



/* class pipex*/

pipex::~pipex()
{
    this -> close_write();
    this -> close_read();
}

pipex::pipex()
{
    if(pipe(fd) < 0){
       fd[0] = -1;
       fd[1] = -1;
    }
}

bool pipex::is_open()const
{
    return fd[0] > 0 || fd[1] > 0;
}

int pipex::close_write()
{
    ::close(fd[1]);
    fd[1] = -1;
}

int pipex::close_read()
{
    ::close(fd[0]);
    fd[0] = -1;
}

int pipex::write_tie(TYPE t)
{
    switch(t){
    case STD_IN:
        dup2(fd[1],STDIN_FILENO);
        break;
    case STD_OUT:
        dup2(fd[1],STDOUT_FILENO);
        break;
    case STD_ERR:
        dup2(fd[1],STDERR_FILENO);
        break;
    default:;
    }
    //TODO testclose(fd[1]);
}

int pipex::read_tie(TYPE t)
{
    switch(t){
    case STD_IN:
        dup2(fd[0],0);
        break;
    case STD_OUT:
        dup2(fd[0],1);
        break;
    case STD_ERR:
        dup2(fd[0],2);
        break;
    default:;
    }
    //TODO return ?
}
/*
int write_tie_file(file_basic&file)
{
    filex& fdx = static_cast<filex&>(file);
    /*down_cast...I know it is dangerous,but we have to do like this*/
/*    
}
*/
