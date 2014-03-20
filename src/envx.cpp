#include"envx.h"

#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>

#include<string>

namespace{
    /*to check if the path or file s is existed*/
    bool test_dir(const std::string&s)
    {
        struct stat buf;
        stat(s.data(),&buf);
        return S_ISDIR(buf.st_mode); 
    }
    bool test_file(const std::string&s)
    {
        struct stat buf;
        stat(s.data(),&buf);
        return S_ISREG(buf.st_mode);
    }
};

int envx::change_dir(const std::string& dir)
{
    if(this -> dir_is_existed(dir))
        return DIR_NOT_EXISTED;
    else if(!chdir(dir.data())){
        return CH_OK;
    }else
        return UNKNOWN_ERROR;
}

bool envx::dir_is_existed(const std::string& dir)const
{
    return test_dir(dir);
}

bool envx::file_is_existed(const std::string& file)const
{
    return test_file(file);
}

std::string envx::where()const
{
    char buf[MAX_PATH_LENGTH+1];
    getcwd(buf,MAX_PATH_LENGTH);
    return std::string(buf);
}
