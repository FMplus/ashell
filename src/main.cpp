#include<iostream>
#include<string>
#include<list>
#include<stdio.h>

#include<dirent.h>
#include<unistd.h>
#include<sys/wait.h>

const static int MAX = 256;
const static char* HOME = "home";

class dir_list
{
  public:
    typedef std::string string;
    typedef std::list<string> list;
    typedef typename list::iterator iterator;
    typedef typename list::const_iterator const_iterator;

    dir_list()
    {
        this -> go_home();
    }

    string combine()
    {
        string buf = "/";
        buf.reserve(sseq.size()*MAX);
        for(const_iterator i = sseq.begin();i != sseq.end();i++)
        {
            buf += *i + "/";
        }
        return buf;
    }

    void push(const std::string&name)
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

    void go_home()
    {
        go_root();
        sseq.push_back(HOME);
    }

    void go_root()
    {
        sseq.clear();
    }
  private:
    list sseq;
};

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

class parser
{
public:
    parser(shl_io_api*iom,runtime*rt)
    :iom(iom),rt(rt)
    {}


    int skip_space(const std::string&s,const int n){
        int i = n;
        while(s[i] == ' '||s[i] == '\t'){
            i++;
        }
        return i;
    }
private:
    std::string line;
    std::string look;
public:
    int scan(){
        static int i = 0;
        look.clear();
        if(i >= line.length()){
             i = 0;
             line =  iom -> get_line();
        }
        i = skip_space(line,i);
        switch(line[i]){
        case '\0':
        case '\n':
            return line[i++];
        default:
           while(line[i] != '\0'&&line[i] != ' '
                &&line[i] != '\n'&&line[i] != '\t'){
            look += line[i];
            i++;
           }
#define IS_SSEQ 257
           return IS_SSEQ;
        }
    }


    void do_parse()
    {
        std::string buf;
        while(true){
            iom -> put_str( dlst.combine() + "#");
            switch(this -> scan()){
            case '\0':
            case '\n':
                continue;
            case IS_SSEQ:
                if(look == "cd"){
                    int i = this->scan();
                    if(i!= '\0'&&i != '\n')
                        buf = look;
                    line.clear();
                    this -> change_dir(buf);
                }else if(look == "dir"){
                    this -> list_dir();
                    line.clear();
                }else if(look == "exit"){
                    return;
                }else{
                    pid_t pid = fork();
                    if(pid == 0){
                        iom -> put_str("It is in child!!!\n");
			rt-> execute(look,dlst.combine());
                    }else if(pid > 0){
                        iom -> put_str("It is in father!!\n");
                        wait(NULL);
                    }else{
                        iom -> put_str("Fork wrong!!!\n");
                    }

                }
            }
        }
    }

    void list_dir()
    {
        std::string tmp = dlst.combine();
        DIR*dir = opendir(tmp.data());
        struct dirent* ent = NULL;
        while(NULL != (ent=readdir(dir))){
            iom -> put_str(std::string(ent -> d_name) + "\n");
        }
        closedir(dir);
    }

    void change_dir(const std::string&path)
    {
        std::string tmp,buf;
        int i = 0;
        if(path[0] == '/'){
            dlst.go_root();
            i++;
        }
        while(i < path.length()){
            for(;path[i] != '/'&&path[i] != '\0';i++){
                buf += path[i];
            }
            if(buf.empty())
                break;
            dlst.push(buf);
            i++;
            buf = "";
        }
    }

private:
    shl_io_api*iom;
    runtime*   rt;
    class dir_list dlst;
};


class console:public shl_io_api,public runtime
{
    public:
          std::string get_line()
          {
                std::string tmp;
                std::getline(std::cin,tmp,'\n');
                return tmp;
          }

          char get_char()
          {
                return getchar();
          }

          void put_char(const char c)
          {
                std::cout<<c;
          }

          void put_str(const std::string&s)
          {
                std::cout<<s;
          }

	  void execute(const std::string&file_name,const std::string&path)
	 {
		char*x[] = {NULL};
                std::string d = path + file_name;
		this -> put_str(d + "\n");
		execve(d.data(),x,x);
	 }
    private:

};


int main()
{
    class console*x = new console;
    parser*p = new parser(x,x);
    p->do_parse();
    delete p;
    delete x;
}
