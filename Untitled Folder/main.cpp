
#include "stringvar.h"
#include "realvar.h"
#include "numericvar.h"
#include "charvar.h"
#include "maps.h"
#include <unistd.h>
#include <vector>


void Save_var(string line);


int main()
{
    

    dtypemap["STRING"] = new StringVar();
    dtypemap["REAL"] = new RealVar();
    dtypemap["NUMERIC"] = new NumericVar();
    dtypemap["CHAR"] = new CharVar();

    ops["ADD"] = new ADD();
    ops["SUB"] = new SUB();
    ops["MUL"] = new MULT();
    ops["DIV"] = new DIV();
    ops["ASSIGN"] = new ASSIGN();
    ops["OUT"] = new OUT();
    ops["SLEEP"] = new Sleep();



    vector <string> lines; // vector to store lines of the mis file
    vector <string> :: iterator i;
    vector <string> :: reverse_iterator ir;

    string line1 = ""; // a string to hold each line to then push back to the vector
    ifstream readFile1("test.mis"); // read mis file
    if(readFile1.good()){
        while(getline(readFile1,line1)){
            lines.push_back(line1);
        }      
        readFile1.close();
    }    
    else{cout<<"Error! Cannot open the file \n"; return -1;}
    for(i = lines.begin(); i != lines.end(); i++)
    {
        string tmp = "";
        string tmp2 = "";
        stringstream is(*i);
        getline(is,tmp,' ');
        for(int j = tmp.length()+1; j<(*i).length();j++){tmp2 += (*i)[j];} // save the rest of the line to tmp2

        if(tmp == "VAR"){Save_var(tmp2);}
        // else if(tmp == "ADD"){ ops["ADD"]->perform(varmap,tmp2); }
        // else if(tmp == "SUB"){ ops["SUB"]->perform(varmap,tmp2); }
        // else if(tmp == "MULT"){ ops["MULT"]->perform(varmap,tmp2); }
        // else if(tmp == "DIV"){ ops["DIV"]->perform(varmap,tmp2); }
        // else if(tmp == "SLEEP"){ ops["SLEEP"]->perform(varmap,tmp2); }
        
        //else if(tmp == "OUT"){ ops["OUT"]->perform(varmap,tmp2); }
        //else{cout<<"Error! Instruction "<<tmp<<" Not Found\n";}
        else{
            operation* obj = ops[tmp];
            if(obj != NULL){
                obj->perform(varmap,tmp2);
            }else cout<<"Undefined Object Identifier\n";
        }
    }

    return 0;
}
void Save_var(string line)
{
    stringstream iss(line);
    string name = "";// The string to hold the name of the object
    string type = "";// The string to hold the type of the object
    getline(iss, name, ',');// parse until the first comma
    getline(iss,type,',');
    Var *obj = dtypemap[type];
    //static_cast<NumericVar*>(obj)
    if(obj != NULL){
        obj = obj->clone(iss);
        varmap[make_pair(name,type)] = obj;
    }else cout<<"Undefined Object Identifier\n";
}