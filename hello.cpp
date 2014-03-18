#include<iostream>
#include<string>

#include<dirent.h>


using namespace std;

    void list_dir()
    {
        //std::string tmp = dlst.combine();
        DIR*dir = opendir(".");
        struct dirent* ent = NULL;
        while(NULL != (ent=readdir(dir))){
            cout<<(std::string(ent -> d_name) + "\n");
        }
        closedir(dir);
    }


int main()
{
	cerr<<"I am here!"<<endl;
	list_dir();	
}
