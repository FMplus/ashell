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
            if(!fork()){
                h.close_read();
                h.close_write();
                wait(NULL);
                wait(NULL);
            }else{
                h.close_read();//sender
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
