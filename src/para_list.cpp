#include"para_list.h"

para_list::para_list()
{}

para_list::para_list(const para_list&b)
:para_seq(b.para_seq){}

para_list::const_iterator para_list::begin()const
{
    return para_seq.begin();
}

para_list::const_iterator para_list::end()const
{
    return para_seq.end();
}

const std::string& para_list::at(const int idx)const
{
    return para_seq[idx];
}

int para_list::size()const
{
    return para_seq.size();
}

void para_list::reserve(const int size)
{
    para_seq.reserve(size);
}

void para_list::clear()
{
    para_seq.clear();
}

void para_list::push(const std::string&para)
{
    para_seq.push_back(para);
}
