#include "charvar.h"

CharVar::CharVar(){}
void CharVar::initialize(stringstream &ss){
    //varcname = p_name;
    string str = "";
    getline(ss, str, ',');
    vchar = str[3];
    //cout<<"variable name: "<<varcname<<' '<<vchar<<endl;
}
Var* CharVar::clone(stringstream &ss){
    CharVar* charvar = new CharVar();
    charvar ->initialize(ss);
    return charvar;
}
char CharVar::getvalue(){return vchar;}
CharVar::~CharVar(){}