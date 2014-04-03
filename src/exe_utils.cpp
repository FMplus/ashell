#include"exe_utils.h"

/*struct exe_info*/

void exe_info::set_pathname(const string&pathname)
{
    this -> pathname = pathname;
}

void exe_info::push_arg(const string&arg)
{
    this -> args.push(arg);
}

const exe_info::string&exe_info::at(const int idx)const
{
    return args.at(idx);
}

const exe_info::string&exe_info::get_path()const
{
    return pathname;
}

void exe_info::clear_arg()
{
    this -> args.clear();
}

/*class execute_list*/

execute_list::execute_list(){}

execute_list::~execute_list()
{
    this -> clear();
}

void execute_list::set_redirected(const bool choice)
{
    last_is_redirected_to_file = choice;
}

bool execute_list::is_redirected()const
{
    return last_is_redirected_to_file;
}

void execute_list::set_pathname(const string&pathname)
{
    redirected_file_name = pathname;
}

const execute_list::string& execute_list::get_pathname()const
{
    return redirected_file_name;
}

void execute_list::push_exenode(exe_info*einfo)
{
    exes.push_back(einfo);
}

exe_info* execute_list::at(const int idx)
{
    return exes.at(idx);
}

int execute_list::size()const
{
    return exes.size();
}

void execute_list::clear()
{
    exes.clear();
}
