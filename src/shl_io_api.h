#ifndef SHL_IO_API
#define SHL_IO_API

#include<string>

class shl_io_api
{
    public:
    virtual std::string get_line() = 0;
    virtual char        get_char() = 0;
    virtual void        put_char(const char c) = 0;
    virtual void        put_str(const std::string&s)  = 0;
};

class runtime
{
      public:
      virtual void execute(const std::string&file_name,const std::string&path) = 0;
};

#endif //SHL_IO_API
