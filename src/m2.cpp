#include<iostream>

#include"parser.h"
#include"console.h"

int main()
{
    console*c = new console;
    parser*p  = new parser(c,c);
    p -> do_parse();
    delete p;
    delete c;
    return 0;
}
