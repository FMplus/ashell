#include<iostream>

#include "parser.h"
#include "console.h"
#include "file_io_api.h"
#include <string.h>
typedef std::string string;

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
    {
        while (counter < argc)
        {
            string str = argv[counter];
            if (str == "-no-stdout\0")
            {
                std::cout << "1.stdout\n";
                mode_stdout = (0<<1);
            }
            else if (str == "-no-stderr\0")
            {
                std::cout << "2.stderr\n";
                mode_stderr = (0<<2);
            }
            else if (str == "-version\0")
            {
                std::cout << "3.version\n";
                //a file of version?
            }
            else if (str == "-help\0")
            {
                std::cout << "4.help\n";
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
        if (mode_inter != 0)
        {
            p = new parser(c,c,c);
            p -> set_mode( mode_inter | mode_stdout | mode_stderr );
            p -> do_parse();
        }
    }


    delete p;
    delete c;
    return 0;
}
