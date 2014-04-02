#include "console.h"
#include "para_list.h"
#include <errno.h>

std::string console::get_line()
{
    std::string tmp;
    std::getline(std::cin,tmp,'\n');
    return tmp;
}

char console::get_char()
{
    return getchar();
}

void console::put_char(const char c)
{
     std::cout<<c;
}

void console::put_str(const std::string&s)
{
    std::cout<<s;
}

void console::execute(const std::string&file_name,const std::string&path)
{
    /*char*args[] = {"/bin/ls",NULL};
    char*envp[] = {"PATH=/bin/",NULL};
    //chdir(path.data());
    std::string d = std::string("/bin/")+file_name;
    //this -> put_str(d + "\n");
    //this -> put_str(path + "\n");
    //this -> put_str(file_name + "\n");
    execve(d.data(),args,envp);
    this -> put_error(d + " executed not well,What happened???\n");
    ::exit(0);*/
}

void console::execute(const std::string&file_name,const para_list&args)
{
    const int SIZE = args.size();
    char** m = new char*[SIZE+2];
    int i = 0, offset = 0, pipesign = 0;
   //std::cout<<"\""<<file_name<<"\""<<std::endl;
    //m[0] = const_cast<char*>(file_name.data());
    m[0] = const_cast<char*>(file_name.data());
    m[SIZE+1] = NULL;
    for( ; i < SIZE; i++ )
    {
        if (*(args.at(i).data()) == '|')
        {
            pipesign = 1;
            m[i+1] = NULL;
            //pipe(offset,i,m,read,write);//not exist now;
            //std::cout << "1:|: " << offset << " " << i << "NULL" << std::endl;
            offset = i + 1;
        }
        else
        {
            m[i+1] = const_cast<char*>(args.at(i).data());
            //std::cout << "2:|: " << offset << " " << i << m[i+1] << std::endl;
        }
    }

    if(!pipesign)
    if (execvp(file_name.data(),m) == -1)
    {
        //std::cout << errno << std::endl;
        switch (errno){
        case EACCES:
            this -> put_error("ERROR : EACCEX : Without execute permission.\n");
            break;
        case EPERM:
            this -> put_error("ERROR : EPERM : Have no root access.\n");
            break;
        case E2BIG:
            this -> put_error("ERROR : E2BIG : Array too big.\n");
            break;
        case ENOEXEC:
            this -> put_error("ERROR : ENOEXEC : Unable to determine file format.\n");
            break;
        case EFAULT:
            this -> put_error("ERROR : EFAULT : Filename is beyond the scope can access the space.\n");
            break;
        case ENAMETOOLONG:
            this -> put_error("ERROR : ENAMETOOLONG : Filename is too long.\n");
            break;
        case ENOENT:
            this -> put_error("ERROR : ENOENT : The Filename not exist.\n");
            break;
        case ENOMEM:
            this -> put_error("ERROR : ENOMEM : The core of memory.\n");
            break;
        case ENOTDIR:
            this -> put_error("ERROR : ENOTDIR : The string of filename is not a valid directory.\n");
            break;
        case ELOOP:
            this -> put_error("ERROR : ELOOP : Too much sympolic links.\n");
            break;
       // case ETXTBUSY:
            //this -> put_error("ERROR : ETXTBUSY : To implement file to open by other processes.\n");
           // break;
        //case EIO_I/O:
            //this -> put_error("ERROR : EIO I/O : Access error.\n");
            //break;
        case ENFILE:
            this -> put_error("ERROR : ENFILE : The system allows the total number of open file has been reached.\n");
            break;
        case EMFILE:
            this -> put_error("ERROR : EMFILE : Has achieved system allows the total number of single process can open the file.\n");
            break;
        case EINVAL:
            this -> put_error("ERROR : EINVAL : To perform file ELF format is not a PT_INTERP.\n");
            break;
        //case EISDIR_ELF:
            //this -> put_error("ERROR : EISDIR ELF : The translator is a directory.\n");
            //break;
       // case ELIBBAD_ELF:
            //this -> put_error("ERROR : ELIBBAD ELF : The translator has problem.\n");
            //break;
        default:
            this -> put_error("ERROR : What happened?\n");
            break;
        }

        delete []m;
    }
    else
        delete []m;
}

void console::put_error(const std::string&s)
{
    std::cerr<<s;
}

void console::exit()
{
    ::exit(0);
}

int console::fork()
{
	return ::fork();
}
