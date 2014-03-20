#ifndef __ENV_X_H
#define __ENV_X_H
#include<string>

#include<unistd.h>

#include"env.h"

#define MAX_PATH_LENGTH 140

class envx:public environment
{
    public:
    //envx();
    int change_dir(const std::string& dir);
    bool dir_is_existed(const std::string& dir) const;
    bool file_is_existed(const std::string& filename) const;
    std::string where()const;
};

#endif  //__ENV_X_H
