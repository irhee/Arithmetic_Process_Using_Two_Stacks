/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <cstring>
#include <string>

using namespace std;
int main()
{
    string s = "Hello World New Way to Parse";
    string p;
    int count = s.length();
    int inc = 0;
    string del = " ";
    int a;
    while(inc < count)
    {
        a = s.find(del);
        if(a == -1)
        {
            break;
        }
        p = s.substr(0,s.find(del));
        cout << p << endl;
        s = s.substr(s.find(del)+1, s.length());
        
        inc += a;
    }
    cout << s << endl;
    
    return 0;
}



