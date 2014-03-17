#include "dir_list.h"

dir_list::dir_list()
{
    this -> go_home();
}

std::string dir_list::combine()
{
    string buf = "/";
    buf.reserve(sseq.size()*MAX);
    for(const_iterator i = sseq.begin();i != sseq.end();i++)
    {
        buf += *i + "/";
    }
    return buf;
}

void dir_list::push(const std::string&name)
{
    if(name == "~"){
        this -> go_home();
    }else if(name == ".."){
        if(!sseq.empty())
            sseq.pop_back();
    }else if(name == ""){

    }else{
        sseq.push_back(name);
    }
}

void dir_list::go_home()
{
    go_root();
    sseq.push_back(HOME);
}

void dir_list::go_root()
{
    sseq.clear();
}
