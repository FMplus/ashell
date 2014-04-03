#include"pipex.h"
#include"pipe_api.h"

#include<unistd.h>
#include<sys/wait.h>

#include<cstdlib>

int main()
{
    pipex h;
    char*var[] = {NULL};
    if(h.is_open()){
        if(fork()){//in father
            if(fork()){
                h.close_read();
                h.close_write();
                wait(NULL);
                wait(NULL);
            }else{
                h.close_read();//sender
                h.read_tie(STD_IN);
                h.write_tie(STD_OUT);
                execve("./sender",var,var);
                exit(0);
            }
        }else{//in child
            h.close_write();
            h.read_tie(STD_IN);
            execve("./getter",var,var);
            exit(0);
        }
    }
    return 0;
}

int pipe(char **m,int m_size)
{
    pipex h;
    int i = 0;
    char*var[] = {NULL};
    if(h.is_open())
    {
        if (fork())
        {
            //当识别到|这个符号时fork一下，之后子进程进行读操作，
        }
        else
        {
            //如果是已经写了东西的那么进行读管道，然后再写
        }
    }
    return 0;
}
