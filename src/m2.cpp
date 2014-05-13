#include<iostream>

#include "parser.h"
#include "console.h"

int main(int argc,char *argv[])
{
    console*c = new console;
    parser*p  = new parser(c,c,c);
    p -> set_mode(MODE_SCRIPT | MODE_STDERR_OPEN | MODE_STDOUT_OPEN);
    p -> do_parse();
    delete p;
    delete c;
    return 0;
}
