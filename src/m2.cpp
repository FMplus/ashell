#include<iostream>

#include "parser.h"
#include "console.h"
#include "file_io_api.h"
#include <string.h>
#include <stdio.h>
#define VERSION_MAIN 0
#define VERSION_SUB 3

typedef std::string string;


#define PROGNAME "ashell"
static int mode_inter = 1;
static int mode_stdout = (1<<1);
static int mode_stderr = (1<<2);
static const char* progname = PROGNAME;
static char* filename;
static int doargs(int argc,char *argv[]);
static void usage(const char* message);
static void vers(const char* message);

int main(int argc,char *argv[])
{
    parser*p = NULL;
    console*c = new console;
    int i = doargs(argc,argv);
    if (mode_inter == 0)
    {
        file_io_api*file = new file_io_api;
        file -> open_file(filename);
        p = new parser(file,c,c);
        p -> set_mode(MODE_SCRIPT|mode_stdout|mode_stderr);
        p -> do_parse();
    }
    else if (i)
    {
        p = new parser(c,c,c);
        p -> set_mode(mode_inter|mode_stdout|mode_stderr);
        p -> do_parse();
    }

    if (p != NULL)
        delete p;
    delete c;
    return 0;
}

#define IS(s)	(strcmp(argv[i],s)==0)

static int doargs(int argc,char *argv[])
{
    int i = 1,version = 0,help = 0;
    progname = argv[0];
    for ( i = 1; i < argc; i++ )
    {
        if (IS("-no-stdout"))
        {
            //printf("close stdout \n");
            mode_stdout = (0<<1);
        }
        else if (IS("-no-stderr"))
        {
            //printf("close stderr \n");
            mode_stderr = (0<<2);
        }
        else if (IS("-version"))
        {
            version++;
        }
        else if (IS("-help"))
        {
            help++;
        }
        else
        {
            if (mode_inter != 0)
            {
                mode_inter = 0;
                filename = argv[i];
            }
            else
            {
                std::cerr<<"Can't recognize the option " <<argv[i]<< " many error!\n";//error;
                return 0;
            }
        }
    }
    if (version)
    {
        vers(progname);
        if (version == (argc - 1))
            exit(EXIT_SUCCESS);
    }
    if (help)
    {
        usage(progname);
        if (help == (argc - 1))
            exit(EXIT_SUCCESS);
    }
    return i;
}

static void vers(const char* message)
{
    printf("version: v%d.%d\n",VERSION_MAIN,VERSION_SUB);
}

static void usage(const char* message)
{
    if (message == progname)
    {
        printf(
            "usage: %s [options] \n"
            "Available options are:\n"
            "-no-stdout    close the stdout\n"
            "-no-stderr    close the stderr\n"
            "-version      show the version information\n"
            "-help         show the usage\n"
            "[filename]    execute command in the file\n"
            ,progname);
        //exit(EXIT_SUCCESS);
    }
    else
    {
        std::cerr << "Error option!" << std::endl;
        exit(EXIT_FAILURE);
    }
}
