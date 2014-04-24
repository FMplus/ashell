#ifndef __ENV_H
#define __ENV_H

#include<string>

#define CH_OK            1
#define DIR_NOT_EXISTED  0
#define UNKNOWN_ERROR    (-1)

class environment
{
    public:
    virtual ~environment(){}
    virtual int change_dir(const std::string& dir) = 0;
    virtual bool dir_is_existed(const std::string& dir) const = 0;
    virtual bool file_is_existed(const std::string& dir) const = 0;
    virtual std::string where() const = 0;
    //virtual std::string
};

#endif//__ENV_H
