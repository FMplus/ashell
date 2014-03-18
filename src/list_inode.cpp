#include "list_inode.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <iostream>

using namespace std;

int main()
{
    class list_inode test;
    struct dirent* ent = NULL;
    DIR *pDir;
    char* path = "/home/hdt/";
    pDir = opendir(path);
    while (NULL != (ent = readdir(pDir)))
    {
        test.insert(ent);
        printf("%s\n",ent -> d_name);
        if (test.find(ent -> d_name) != NULL)
        {
            printf("01.....\n");
        }
        else
        {
            printf("wrong\n");
        }
    }
    if (test.find(".001001") != NULL)
    {
        printf("001....\n");
    }
    else
    {
        printf("wrong001\n");
    }

    if (test.find(".pulse-cookie") != NULL)
    {
        printf("002....\n");
    }
    else
    {
        printf("wrong002\n");
    }

    if (test.find(".goutputstream-GZNE4W") != NULL)
    {
        printf("003....\n");
    }
    else
    {
        printf("wrong003\n");
    }

    test.clear();
    if (test.find(".goutputstream-GZNE4W") != NULL)
    {
        printf("004....\n");
    }
    else
    {
        printf("wrong004\n");
    }
    return 0;
}
