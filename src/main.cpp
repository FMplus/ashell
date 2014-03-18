#include<iostream>
#include<string>
#include<list>
#include<stdio.h>

#include<dirent.h>
#include<unistd.h>
#include<sys/wait.h>
#include "dir_list.h"
#include "console.h"
#include "parser.h"

int main()
{
    class console*x = new console;
    parser*p = new parser(x,x);
    p->do_parse();
    delete p;
    delete x;
}
