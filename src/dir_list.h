#ifndef DIR_LIST
#define DIR_LIST

#include<iostream>
#include<string>
#include<list>

const static int MAX = 256;
const static char* HOME = "home";

class dir_list
{
  public:
    typedef std::string string;
    typedef std::list<string> list;
    typedef typename list::iterator iterator;
    typedef typename list::const_iterator const_iterator;

    dir_list();
    string combine();
    void push(const std::string&name);
    void go_home();
    void go_root();

  private:
    list sseq;
};

#endif //DIR_LIST
