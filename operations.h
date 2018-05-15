#include <map>
#include "var.h"
#include <time.h>
#include <unistd.h>

using namespace std;

class operation
{
    public:
        NumericVar* setv1 = 0; 
        RealVar* setv2 = 0;
        StringVar* setv3 = 0;
        CharVar* setv4 = 0;
        operation(){} // Constructor
        //virtual void perform(int* a, string x) = 0;
        //virtual void initialize(stringstream & ss)=0;
        //virtual operation * clone(stringstream & ss)=0;
        typedef  array<pair<string,string>,4> pair_array;

        pair_array Pair1(string v){
            pair_array keys = {make_pair(v,"NUMERIC"), make_pair(v,"REAL"),make_pair(v,"STRING"),make_pair(v,"CHAR") };
            return keys;
        }

        virtual void perform(map <pair<string,string>, Var*>& getmap, string opline) = 0; // a virtual function that takes variable map to get the value of the variable and a line string of variables and constants
        virtual ~operation(){} // Destructor
};

class ADD: public operation
{
    private:
    public:
        ADD(){}
        void perform(map <pair<string,string>, Var*>& getmap, string opline)
        {
            cout<<"this is ADD op\n";
            string str = "";
            string var="";
            
            
            double new_var=0; // a variable to store the sum of the numbers
            string newvar;
            string new_var_name=""; // the variable name that will store the numbers ( the first parameter)
            stringstream iss(opline);
            getline(iss,new_var_name,','); // parse the given line to the first comma which is the storing variable
            // getline(iss,newvar,',');
                 
            pair_array p1 = Pair1(new_var_name);

            if(getmap.find(p1[0]) != getmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                new_var = tmp->getvalue(); // add the value to new_var
                setv1 = tmp;
            }
        
            else if(getmap.find(p1[1]) != getmap.end()){// to get real value
                RealVar* tmp = dynamic_cast<RealVar*>(getmap[p1[1]]);
                new_var = tmp->getvalue();
                setv2 = tmp;
            }
            else{cout<<"There are no variable with that name "<<new_var_name<<"\n"; return;}

            // pair_array p2 = Pair1(newvar);

            // if(newvar[0] == '$')
            // {
            //     if(getmap.find(p2[0]) != getmap.end()){ // to get numeric value
            //         NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p2[0]]);
            //         new_var += tmp->getvalue(); // add the value to new_var
            //     }
            //     else if(getmap.find(p2[1]) != getmap.end()){// to get real value
            //         RealVar* tmp = dynamic_cast<RealVar*>(getmap[p2[1]]);
            //         new_var += tmp->getvalue();
            //     }
            //         else{cout<<"There are no variable with that name "<<newvar<<"\n";}
                    
            // }else
            //     new_var += stof(newvar);
            while(getline(iss,str,','))
            {
                if(str[0] == '$'){
                    
                    pair_array p3 = Pair1(str);
                    if(getmap.find(p3[0]) != getmap.end()){ // to get numeric value
                        NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p3[0]]);
                        new_var += tmp->getvalue(); // add the value to new_var
                    }
                    else if(getmap.find(p3[1]) != getmap.end()){// to get real value
                        RealVar* tmp = dynamic_cast<RealVar*>(getmap[p3[1]]);
                        new_var += tmp->getvalue();
                    }
                    else{cout<<"There are no variable with that name "<<str<<"\n";}
                    
                    
                }
                else{
                    new_var += stof(str);
                    str = "";}
            }
            if(setv1 != 0) {setv1->setvalue(new_var); setv1 = 0;}
            else if(setv2 !=0 ){setv2 ->setvalue(new_var); setv2 = 0;}
            str = "";
            cout<<new_var<<endl;
            // the new_var is the variable that hold the result after the add operation
        }
        ~ADD(){}
};


class SUB: public operation
{
    public:
        SUB(){}
        void perform(map <pair<string,string>, Var*>& getmap, string opline)
        {
            cout<<"this is SUB op\n";
            double new_var=0; // a variable to store the divid of the numbers

            string second_p="";
            string first_p=""; // the variable name that will store the numbers ( the first parameter)
            string third_p="";

            stringstream iss(opline);
            getline(iss,first_p,','); // parse the given line to the first comma which is the storing variable
            getline(iss,second_p,',');
            getline(iss,third_p,',');
             // create an object from struct pair

            pair_array p2 = Pair1(second_p);
            // save the second value to new_var variable to subtract the third parameter from it
            if(second_p[0] == '$')
            {
                if(getmap.find(p2[0]) != getmap.end()){ // to get numeric value
                    NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p2[0]]);
                    new_var = tmp->getvalue(); // add the value to new_var
                }
                else if(getmap.find(p2[1]) != getmap.end()){// to get real value
                    RealVar* tmp = dynamic_cast<RealVar*>(getmap[p2[1]]);
                    new_var = tmp->getvalue();
                }
                else{cout<<"There are no variable with that name !"<<second_p<<"\n"; return;}
                    
            }else
                new_var = stof(second_p);

            // get the value of the third parameter and subtract it from the second one
            pair_array p3 = Pair1(third_p);
            if(third_p[0] == '$')
            {
                if(getmap.find(p3[0]) != getmap.end()){ // to get numeric value
                    NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p3[0]]);
                    new_var -= tmp->getvalue(); // add the value to new_var
                }
                else if(getmap.find(p3[1]) != getmap.end()){// to get real value
                    RealVar* tmp = dynamic_cast<RealVar*>(getmap[p3[1]]);
                    new_var -= tmp->getvalue();
                }
                else{cout<<"There are no variable with that name !"<<third_p<<"\n";return;}
                    
            }else
                new_var -= stof(third_p); 

            // save the result to the first parameter    
            pair_array p1 = Pair1(first_p);
            if(getmap.find(p1[0]) != getmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                tmp->setvalue(new_var);
            }
            else if(getmap.find(p1[1]) != getmap.end()){// to get real value
                RealVar* tmp = dynamic_cast<RealVar*>(getmap[p1[1]]);
                tmp->setvalue(new_var);
            }
            else{cout<<"There are no variable with that name "<<first_p<<"\n";return;}
            
            cout<<new_var<<endl;

        }
        ~SUB(){}
};

class MULT: public operation
{
    public:
        MULT(){}
         void perform(map <pair<string,string>, Var*>& getmap, string opline)
        {
            cout<<"this is MUL op\n";
            string str = "";
            string var="";
            
            
            double new_var=0; // a variable to store the sum of the numbers
            string newvar;
            string new_var_name=""; // the variable name that will store the numbers ( the first parameter)
            stringstream iss(opline);
            getline(iss,new_var_name,','); // parse the given line to the first comma which is the storing variable
                 
            pair_array p1 = Pair1(new_var_name);

            if(getmap.find(p1[0]) != getmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                new_var = tmp->getvalue(); // add the value to new_var
                setv1 = tmp;
            }
        
            else if(getmap.find(p1[1]) != getmap.end()){// to get real value
                RealVar* tmp = dynamic_cast<RealVar*>(getmap[p1[1]]);
                new_var = tmp->getvalue();
                setv2 = tmp;
            }
            else{cout<<"There are no variable with that name "<<new_var_name<<"\n"; return;}

            while(getline(iss,str,','))
            {
                if(str[0] == '$'){
                    
                    pair_array p3 = Pair1(str);
                    if(getmap.find(p3[0]) != getmap.end()){ // to get numeric value
                        NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p3[0]]);
                        new_var *= tmp->getvalue(); // add the value to new_var
                    }
                    else if(getmap.find(p3[1]) != getmap.end()){// to get real value
                        RealVar* tmp = dynamic_cast<RealVar*>(getmap[p3[1]]);
                        new_var *= tmp->getvalue();
                    }
                    else{cout<<"There are no variable with that name "<<str<<"\n";}
                    
                    
                }
                else{
                    new_var *= stof(str);
                    str = "";}
            }
            if(setv1 != 0) {setv1->setvalue(new_var); setv1 = 0;}
            else if(setv2 !=0 ){setv2 ->setvalue(new_var); setv2 = 0;}
            str = "";
            cout<<new_var<<endl;
            // the new_var is the variable that hold the result after the add operation
        }
        ~MULT(){}
};

class DIV: public operation
{
    public:
        DIV(){}
        void perform(map <pair<string,string>, Var*>& getmap, string opline)
        {
            cout<<"this is DIV op\n";
            double new_var=0; // a variable to store the divid of the numbers

            string second_p="";
            string first_p=""; // the variable name that will store the numbers ( the first parameter)
            string third_p="";

            stringstream iss(opline);
            getline(iss,first_p,','); // parse the given line to the first comma which is the storing variable
            getline(iss,second_p,',');
            getline(iss,third_p,',');
             // create an object from struct pair
            
            pair_array p2 = Pair1(second_p);
            if(second_p[0] == '$')
            {
                if(getmap.find(p2[0]) != getmap.end()){ // to get numeric value
                    NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p2[0]]);
                    if(tmp->getvalue() != 0)
                        new_var = tmp->getvalue(); // add the value to new_var
                    else{cout<<"Error divisible by zero "<<'\n';return;}
                }
                else if(getmap.find(p2[1]) != getmap.end()){// to get real value
                    RealVar* tmp = dynamic_cast<RealVar*>(getmap[p2[1]]);
                    if(tmp->getvalue() != 0)
                        new_var = tmp->getvalue(); // add the value to new_var
                    else{cout<<"Error divisible by zero "<<'\n';return;}
                }
                else{cout<<"There are no variable with that name "<<second_p<<"\n";return;}
                    
            }else
                new_var = stof(second_p);

            pair_array p3 = Pair1(third_p);
            if(third_p[0] == '$')
            {
                if(getmap.find(p3[0]) != getmap.end()){ // to get numeric value
                    NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p3[0]]);
                    if(tmp->getvalue() != 0)
                        new_var /= tmp->getvalue(); // add the value to new_var
                    else{cout<<"Error divisible by zero "<<'\n';return;} // add the value to new_var
                }
                else if(getmap.find(p3[1]) != getmap.end()){// to get real value
                    RealVar* tmp = dynamic_cast<RealVar*>(getmap[p3[1]]);
                    if(tmp->getvalue() != 0)
                        new_var /= tmp->getvalue(); // add the value to new_var
                    else{cout<<"Error divisible by zero "<<'\n';return;}
                }
                else{cout<<"There are no variable with that name "<<third_p<<"\n";return;}
                    
            }else
                new_var /= stof(third_p);

            pair_array p1 = Pair1(first_p);
            if(getmap.find(p1[0]) != getmap.end()){ // to get numeric value
                NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                tmp->setvalue(new_var);
            }
            else if(getmap.find(p1[1]) != getmap.end()){// to get real value
                RealVar* tmp = dynamic_cast<RealVar*>(getmap[p1[1]]);
                tmp->setvalue(new_var);
            }
            else{cout<<"There are no variable with that name "<<first_p<<"\n";return;}

            cout<<new_var<<endl;

        }
        ~DIV(){}
};
class ASSIGN: public DIV
{
    public:
        ASSIGN(){}
        void perform(map <pair<string,string>, Var*>& getmap, string opline)
        {
            string newvar="";
            //double new_var=0;

            string new_var_name=""; // the variable name that will store the numbers ( the first parameter)
            stringstream iss(opline);
            getline(iss,new_var_name,','); // parse the given line to the first comma which is the storing variable
            getline(iss,newvar,',');
          //  cout<<newvar<<endl;
             // create an object from struct pair
            pair_array p1 = Pair1(new_var_name); 
            
            
            if(newvar[0] == '$')
            {
                pair_array p2 = Pair1(newvar);
                if((getmap.find(p1[0]) != getmap.end()) && (getmap.find(p2[0]) != getmap.end()) ){ // to check if the two variables are numeric value
                    NumericVar* tmp1 = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                    NumericVar* tmp2 = dynamic_cast<NumericVar*>(getmap[p2[0]]);
                    tmp1->setvalue(tmp2->getvalue()); // Assign the value of second variable to the first one
                }
                else if((getmap.find(p1[1]) != getmap.end()) && (getmap.find(p2[1]) != getmap.end()) ){ // to check if the two variables are real value
                    RealVar* tmp1 = dynamic_cast<RealVar*>(getmap[p1[1]]);
                    RealVar* tmp2 = dynamic_cast<RealVar*>(getmap[p2[1]]);
                    tmp1->setvalue(tmp2->getvalue());
                }
                else if((getmap.find(p1[2]) != getmap.end()) && (getmap.find(p2[2]) != getmap.end()) ){ // to check if the two variables are string value
                    StringVar* tmp1 = dynamic_cast<StringVar*>(getmap[p1[2]]);
                    StringVar* tmp2 = dynamic_cast<StringVar*>(getmap[p2[2]]);                    
                    tmp1->setvalue(tmp2->getvalue());
                }
                else if((getmap.find(p1[3]) != getmap.end()) && (getmap.find(p2[3]) != getmap.end()) ){ // to check if the two variables are char value
                    CharVar* tmp1 = dynamic_cast<CharVar*>(getmap[p1[3]]);
                    CharVar* tmp2 = dynamic_cast<CharVar*>(getmap[p2[3]]);
                    tmp1->setvalue(tmp2->getvalue());
                }
                    else{cout<<"Error cannot find a variable or cannot assign different data type of values\n";}
                    
            }
            else if(newvar[0] == '"'){
                if((getmap.find(p1[2]) != getmap.end())){ // to check if the two variables are string value
                    StringVar* tmp1 = dynamic_cast<StringVar*>(getmap[p1[2]]);              
                    tmp1->setvalue(newvar);
                }else{cout<<"Cannot find the variable "<<new_var_name<<"\n";}
            }
            else if(newvar[0] == '\''){
                if((getmap.find(p1[3]) != getmap.end())){ // to check if the two variables are string value
                    CharVar* tmp1 = dynamic_cast<CharVar*>(getmap[p1[3]]);              
                    tmp1->setvalue(newvar[1]);
                }else{cout<<"Cannot find the variable "<<new_var_name<<"\n";}
            }
            else{
                 if((getmap.find(p1[0]) != getmap.end()) ){ // to check if the two variables are numeric value
                    NumericVar* tmp1 = dynamic_cast<NumericVar*>(getmap[p1[0]]);                   
                    tmp1->setvalue(stol(newvar)); // Assign the value of second variable to the first one
                }
                else if((getmap.find(p1[1]) != getmap.end())){ // to check if the two variables are real value
                    RealVar* tmp1 = dynamic_cast<RealVar*>(getmap[p1[1]]);
                    tmp1->setvalue(stod(newvar));
                }
            }
                
        }
        ~ASSIGN(){}
};
class OUT: public operation
{
    public:
        OUT(){}
        void perform(map <pair<string,string>, Var*>& getmap, string opline)
        {
            string var="";
            stringstream iss(opline);
            while (getline(iss,var,','))
            {
                if(var[0] == '$'){
                      pair_array p1 = Pair1(var);
                    if(getmap.find(p1[0]) != getmap.end()){ // to get numeric value
                        NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p1[0]]);
                        cout<<tmp->getvalue()<<"\t";// add the value to new_var
                    }
                    else if(getmap.find(p1[1]) != getmap.end()){// to get real value
                        RealVar* tmp = dynamic_cast<RealVar*>(getmap[p1[1]]);
                        cout<<tmp->getvalue()<<"\t";
                    }
                    else if(getmap.find(p1[2]) != getmap.end()){// to get string value
                        StringVar* tmp = dynamic_cast<StringVar*>(getmap[p1[2]]);
                        cout<<tmp->getvalue()<<"\t";
                    }
                    else if(getmap.find(p1[3]) != getmap.end()){// to get char value
                        CharVar* tmp = dynamic_cast<CharVar*>(getmap[p1[3]]);
                        cout<<tmp->getvalue()<<"\t";
                    }
                    else{cout<<"There are no variable with that name !\n";}
                    var = "";
                    
                }
                else  cout<<var<<endl;
            }
        }
};
class Sleep: public operation
{
    public:
    Sleep(){}
    void perform(map <pair<string,string>, Var*>& getmap, string opline)
    {
        if(opline[0] == '$')
        {
            pair_array p2 = Pair1(opline);
            if(getmap.find(p2[0]) != getmap.end()){ // to get numeric value
                    NumericVar* tmp = dynamic_cast<NumericVar*>(getmap[p2[0]]);
                    usleep((tmp->getvalue())); // add the value to new_var
                }
                else if(getmap.find(p2[1]) != getmap.end()){// to get real value
                    RealVar* tmp = dynamic_cast<RealVar*>(getmap[p2[1]]);
                    usleep((tmp->getvalue()));
                }
                else{cout<<"There are no variable with that name !"<<opline<<"\n"; return;}
        }
        else
        usleep(stof(opline));
    }
    ~Sleep(){}

};
class SET_STR_CHAR: public operation
{
    public:
    SET_STR_CHAR(){}
    void perform(map <pair<string,string>, Var*>& getmap, string opline)
    {
        int index = 0;
        char swap ;
        
        string tmpint = "";
        string tmpchr = "";
        string varx ="";
        stringstream iss(opline);

        getline(iss, varx, ',');
        getline(iss, tmpint, ',');
        getline(iss, tmpchr, ',');
        index = stoi(tmpint);
        swap = tmpchr[1];

        if(varx[0] == '$')
        {
            pair_array p2 = Pair1(varx);
            if(getmap.find(p2[2]) != getmap.end()){// to get string value
                StringVar* tmp = dynamic_cast<StringVar*>(getmap[p2[2]]);
                varx = tmp->getvalue();
                if(index > varx.length())
                    cout<<"Index error! out of range\n";
                else{
                    varx[index] = swap;                
                    tmp->setvalue(varx);
                }
            }
                else{cout<<"There are no variable with that name !"<<opline<<"\n"; return;}
        }else{cout<<"Syntax error!\n";}
    }    
};