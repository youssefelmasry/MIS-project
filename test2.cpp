#include <iostream>
#include <string>
#include <sstream>
 
using namespace std;
 
int main()
{
    string x = "ahmed,samir,ramy";
    string y = "";
    stringstream iss(x);
    while(getline(iss,y, ',')){cout<<y<<endl;}
    return 0;
 
}