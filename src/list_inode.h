#ifndef LIST_INODE
#define LIST_INODE
#include"shl_icontainer.h"
#include <list>
#include <string>


class list_inode:public shl_icontainer
{
public:
       typedef std::list<file_node*>::iterator iterator;
       list_inode(){};
       file_node* find(const std::string&pathname);
       void insert(file_node*tmp);
       void erase(file_node*tmp);
       void erase(const std::string&pathname);
       void clear();
       ~list_inode(){};

private:
        std::list<file_node*> iseq;
};

file_node* list_inode::find(const std::string&pathname)
{
        for(iterator i = iseq.begin();i != iseq.end();i++)
        {
                if(pathname == std::string((*i) -> d_name))
                {
                        return (*i);
                }
        }
        return NULL;
}

void list_inode::insert(file_node*tmp)
{
       if (tmp != NULL)
       {
            iseq.push_back(tmp);
       }
}

void list_inode::erase(file_node*tmp)
{
   for (iterator i = iseq.begin();i != iseq.end();i++)
   {
       if ((tmp) == (*i))
       {
           iseq.remove(tmp);
           return;
       }
   }
}

void list_inode::erase(const std::string&pathname)
{
    file_node* temp = find(pathname);
    if (temp == NULL)
        return;
    else
        iseq.remove(temp);
}

void list_inode::clear()
{
   iseq.clear();
}

#endif //LIST_INODE
