#include<iostream>
#include<string>

#include"para_list.h"
std::string buffer;

using namespace std;

static std::string look = "";
std::string buf;

#define S_SEQ 256

int scan()
{
    static int i = 0;
    char peek;
    if(i == buf.length())
    {
        getline(cin,buf,'\n');
        i = 0;
       // cout<<buf<<endl;
    }
    while(buf[i] == ' ' || buf[i] == '\t')
        i++;
    look.clear();

    l2:
    switch(buf[i]){
    case '\0':case '\n':
        return buf[i++];
    case ' ':case '\t':
        //this is impossible,
        return buf[i];    
    case '\"':case '\'':
    {
        char c = buf[i++];
        l: 
        while(buf[i] != '\0' && buf[i] != c){
            if(buf[i] == '\\' ){
               i++;
               if(buf[i] == '\"'||buf[i] == '\''){
                    look += buf[i++];
                }
               else
                    look += '\\';
            }
            look += buf[i++];
        }
        if(buf[i] == '\0'){
            look += '\n';
            getline(cin,buf,'\n');
            i = 0;
            goto l;
        }
        i++;
        if(buf[i] != '\0' && buf[i] != ' ' && buf[i] != '\t')
            goto l2;
        if(buf[i] == '\0'){
            buf = " ";
            i = 0;
        }
        break;
    }
    default:
        do{
            look += buf[i++];
        }while(buf[i] != '\0' && buf[i] != ' ' && buf[i] != '\t');
        if(buf[i] == '\0'){
            buf = " "; 
            i = 0;
        }
    }
    return S_SEQ; 
}

void parser()
{
     switch(scan()){
     case '\0':case '\n':
        {};break;
     case S_SEQ:
        {
            para_list temp;
            string name = look;
            while(scan() == S_SEQ){
                temp.push(look);
                cout<<look<<endl;
            }
            for(int i = 0;i < temp.size();i++)
                cout<<","<<temp.at(i);
            cout<<endl<<"::"<<name<<endl;
        }
     default:
        return;
     }
}

int main()
{
    parser();
}

