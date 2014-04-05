#include"pipex.h"
#include"pipe_api.h"

#include<unistd.h>
#include<sys/wait.h>
#include<iostream>
#include<cstdlib>

int main()
{
    pipex h;
    char*var[] = {NULL};
    if(h.is_open()){
        if(fork()){
            if(fork()){
                if(fork()){//in father
                std::cout << "father" << std::endl;
                h.close_read();
                h.close_write();
                wait(NULL);
                wait(NULL);
                }else{
                    std::cout << "sender" << std::endl;
                    h.close_read();
                    h.write_tie(STD_OUT);
                    execve("./sender",var,var);
                    exit(0);
                }
            }else{
                std::cout << "getsender" << std::endl;
                h.close_write();
                h.read_tie(STD_IN);
                h.write_tie(STD_OUT);
                execve("./getsender",var,var);
                h.close_read();
                h.close_write();
                //h.read_tie(STD_IN);
                //h.write_tie(STD_OUT);
                //execve("./getsender",var,var);
                exit(0);
            }
        }else{//in child
            std::cout << "getter" << std::endl;
            h.close_write();
            h.read_tie(STD_IN);
            execve("./getter",var,var);
            exit(0);
        }
    }
    return 0;
}

/*int pipe(char **m,int m_size)
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
}*/
