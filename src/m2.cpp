#include<iostream>

#include "parser.h"
#include "console.h"
#include "file_io_api.h"
#include <string.h>

int main(int argc,char *argv[])
{
    parser*p;
    console*c = new console;
    if (argc == 1)
    {
        p = new parser(c,c,c);

    }
    else
    {
        file_io_api*file = new file_io_api;
        file -> open_file(argv[1]);
        p = new parser(file,c,c);

    }
    //parser*p  = new parser(c,c,c);
    p -> set_mode(MODE_SCRIPT | MODE_STDERR_OPEN | MODE_STDOUT_OPEN);
    p -> do_parse();
    delete p;
    delete c;
    return 0;
}
