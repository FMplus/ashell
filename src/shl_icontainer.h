#ifndef SHL_I_CONTAINER

#define SHL_I_CONTAINER
#include <string>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

typedef struct dirent file_node;

class shl_icontainer
{
    public:
       shl_icontainer(){}
       virtual file_node* find(const std::string&pathname) = 0;
       virtual void insert(file_node*tmp)                  = 0;
       virtual void erase(file_node*tmp)                   = 0;
       virtual void erase(const std::string&pathname)      = 0;
       virtual void clear()                                = 0;
       virtual ~shl_icontainer(){}
};
#endif
