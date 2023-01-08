#include <iostream>
#include <cstdio>
#include <string.h>
#include "lex.yy.h"
#include "sql.tab.h"
#include "sql.h"
using namespace std;

// int main(int argc, char **argv)
// {
//     while (1)
//     {
//         char csql[1024];
//         memset(csql, 0, sizeof(csql));
//         string s = "CREATE DATABASE ZXX;\n";

//         // fgets(csql, 1024, stdin);
//         strcpy(csql, s.c_str());
//         cout << sizeof(csql);
//         YY_BUFFER_STATE buf = yy_scan_string(csql);
//         yyparse();

//     }
//     return ;
// }

int main(int argc, char **argv)
{
    while (1)
    {
        char csql[1024];
        memset(csql, 0, sizeof(csql));
        string s = "CREATE DATABASE ZXX;ll";
        // int i = 2;
        while (1)
        {
            fgets(csql, 1024, stdin);
            // strcpy(csql, s.c_str());
            cout << sizeof(csql);
            YY_BUFFER_STATE buf = yy_scan_string(csql);
            yyparse();
        }

        return 0;
    }
}

// int main(int argc, char ** argv)
// {
//     char* in_str;
//     cin.getline(in_str, 150);
//      char *buff = (char *)malloc(strlen(in_str) + 2);
//          // 要以两个'\0'结束
//     memset(buff, 0, strlen(in_str) + 2);
//     strcpy(buff, in_str);
//     cout << buff;
//     YY_BUFFER_STATE buffer = yy_scan_buffer(buff, strlen(in_str) + 2);
//     yyparse();

//     yy_delete_buffer(buffer);
//     free(buff);
// }