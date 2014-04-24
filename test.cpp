#include<iostream>

#include<unistd.h>
#include<sys/wait.h>


/* test code for the shell*/

/*Test for the env path of the execve*/

char fn[] = "/home/lsm/dev/ashell/hello";
char dp[] = "/home/";

void ex() {
	char* arg_para[] = {NULL};
	char* env_path[] = {NULL};
    chdir(dp);
	execve(fn,arg_para,env_path);
	std::cerr<<"What happened!?"<<std::endl;
	//exit(0);
}

int main()
{
   if(!fork()){
       	ex();
   }
   wait(NULL);
   return 0;
}
