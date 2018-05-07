#include "var.h"

class CharVar: public Var{
    protected:
        char vchar; // A variable of type char to hold the value char
       // string varcname = ""; // A string to hold the name of the char variable
    public:
        CharVar(); // Constructor
        char getvalue();
        void setvalue(char x){vchar = x;}
        void initialize(stringstream &ss); // A method that initializes the object from a stringstream
        virtual Var* clone(stringstream &ss); // Factory Clone method
        virtual ~CharVar(); // Destructor
};