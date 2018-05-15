#include "stringvar.h"

StringVar::StringVar(){}
//StringVar::StringVar(char* p_vname, short int len): vname(p_vname),length(len),Var(){}
void StringVar::initialize(stringstream &ss)
{
   // varsname = n; // assign the given variable name to varname
    string str = ""; // a string to hold the rest of parsed line
    getline(ss,str,','); // parse the line to the first comma to get the size of the array
    length = stoi(str); // convert the size of array from string to integer
    getline(ss,str,','); // parse the line to the second comma to get the string
    vstring = new char[length]; // initialize the array dynamacilly with the given size
    str = str.substr(0,str.size()); // remove the double quote from the string
    strcpy(vstring,str.c_str()); // assign the string to the array of char
    // test cases
    // for(int i = 0; i<strlen(vstring); i++){
    //     cout<<vstring[i];
    // }
    // cout<<endl;
}

Var * StringVar::clone(stringstream & ss){
    StringVar * stringvar = new StringVar();
    stringvar->initialize(ss);
    return stringvar;
}

void StringVar::setvalue(string x){strcpy(vstring,x.c_str());}

char* StringVar::getvalue(){return vstring;}
StringVar::~StringVar(){}
