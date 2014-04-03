#ifndef _EXE_UTILS_H
#define _EXE_UTILS_H

#include"para_list.h"

#include<string>
#include<vector>

struct exe_info{
    typedef std::string string;

    para_list args;
    string pathname;

    void set_pathname(const string&);
    void push_arg(const string&);
    const string&at(const int )const;
    const string&get_path()const;
    void clear_arg();
};


/*
 * NOTE: This class will manage the memory release of exe_info*
 *       DON'T DO THE DELETE JOB BEYOND the class;
 */
class execute_list{
    public:
    typedef std::string             string;
    typedef std::vector<exe_info*>   exe_list;
    private:
    bool last_is_redirected_to_file;
    string redirected_file_name;
    public:
    exe_list exes;
    public:
    execute_list();//consructor
    ~execute_list();//destructor
    public:
    void set_redirected(const bool choice);//set last is redirected
    bool is_redirected()const;//last exe is redirected
    void set_pathname(const string&);
    const string&get_pathname()const;
    void push_exenode(exe_info*);//push the exe node info to the container
    exe_info*at(const int);//get the exe node at
    int size()const;//get the size
    public:
    void clear();//clear the content
};//class execute_list

#endif //_EXE_UTILS_H
