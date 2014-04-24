#include<string>
#include<iostream>

using namespace std;

int main()
{
    string tmp;
    getline(cin,tmp,'\n');
    cerr<<tmp<<"-->from "<<__FILE__<<endl;
}
