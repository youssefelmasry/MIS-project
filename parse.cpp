#include "parse.h"
Parse::Parse(){}
void Parse::parsing(string filename, vector <string>& vec){
    string line1 = ""; // a string to hold each line to then push back to the vector
    ifstream readFile1(filename); // read mis file
    if(readFile1.good()){
        while(getline(readFile1,line1)){
            vec.push_back(line1);
        }
        readFile1.close();
    }
    else{cout<<"Error! Cannot open the file \n";}
}
Parse::~Parse(){}