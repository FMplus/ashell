#ifndef PARA_LIST
#define PARA_LIST

#include<list>
#include<string>
#include<vector>

class para_list{
    public:
    typedef std::string          string;
    typedef std::vector<string>  str_seq;
    typedef para_list            self;
    typedef const self           const_self;
    //typedef int  size_t;
    typedef str_seq::const_iterator const_iterator;

    para_list();
    para_list(const_self&b);
    const_iterator begin()const;
    const_iterator end()const;
    const string&at(const int idx)const;
    int size()const;
    void reserve(const int size);
    void clear();
    void push(const string&para);

    private:
    str_seq     para_seq;
};//para_list

#endif //PARA_LIST
