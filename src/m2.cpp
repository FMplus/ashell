#include<iostream>

#include "parser.h"
#include "console.h"
#include "file_io_api.h"
#include <string.h>

int main(int argc,char *argv[])
{
    int mode_inter = 1, mode_stdout = (1<<1), mode_stderr = (1<<2);
    int counter = 1;
    parser*p;
    console*c = new console;
    if (argc == 1)
    {
        p = new parser(c,c,c);
        p -> do_parse();
    }
    else
    while (counter < argc)
    {
        if (argv[counter] == "-no-stdout")
        {
            mode_stdout = (0<<1);
        }
        else if (argv[counter] == "-no-stderr")
        {
            mode_stderr = (0<<2);
        }
        else if (argv[counter] == "-version")
        {
            //a file of version?
        }
        else if (argv[counter] == "-help")
        {
            //a file of help?
        }
        else
        {
            file_io_api*file = new file_io_api;
            file -> open_file(argv[counter]);
            p = new parser(file,c,c);
            mode_inter = 0;
            p -> set_mode( mode_inter | mode_stdout | mode_stderr );
            p -> do_parse();
            //file -> close()
            delete file;
        }
        counter++;
    }
    //p -> do_parse();
    //p -> set_mode(mode_inter |mode_stdout |mode_stderr );

    delete p;
    delete c;
    return 0;
}
