#ifndef SHL_IO_API
#define SHL_IO_API

#include<string>
#include"para_list.h"

class shl_io_api
{
    public:
    virtual ~shl_io_api(){}
    virtual std::string get_line() = 0;
    virtual char        get_char() = 0;
    virtual void        put_char(const char c) = 0;
    virtual void        put_str(const std::string&s)  = 0;
    virtual void        put_error(const std::string&s) = 0;
};

class runtime
{
    public:
    virtual void execute(const std::string&file_name,const std::para_list&args) = 0;
    virtual void execute(const std::string&file_name,const std::string&path) = 0;
    virtual ~runtime(){}
    virtual void exit()	= 0;
    virtual int  fork()
    {
	return 0;
    }
	//
};

#endif //SHL_IO_API
