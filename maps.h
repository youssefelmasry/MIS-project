#include "operations.h"
map <pair<string,string>, Var*> varmap; //(variable map) map that has two keys to search for the variable and a value pointer to the passed object from cloning
map<string,operation *> ops; 
map <string, Var *> dtypemap; // (data type map) a map that hold the data type and a pointer to the corrosponding object