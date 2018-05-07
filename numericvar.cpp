#include "numericvar.h"

NumericVar::NumericVar(){}
void NumericVar::initialize(stringstream &ss){
    //varnname = p_name; // assign the given variable name to varnname holder
    string str = ""; // a string to hold the rest of parsed line
    getline(ss,str,','); // parse the line to the first comma to get the value
    vnumeric = stoi(str); // convert the value from string to integer

}
Var* NumericVar::clone(stringstream &ss){
    NumericVar * numericvar = new NumericVar();
    numericvar->initialize(ss);
    return numericvar;
}
long NumericVar::getvalue(){return vnumeric;}
NumericVar::~NumericVar(){}
