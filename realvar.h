#include "var.h"

class RealVar: public Var{
    protected:
        double vreal = 0.0; // double to hold the decimal value
        //string varrname = ""; // A string to hold the real varialble name 
    public:
        RealVar(); // constructor
        double getvalue();
        void setvalue(double x);
        void initialize(stringstream &ss); // A method that initializes the object from a stringstream
        virtual Var* clone(stringstream &ss); // Factory Clone method
        virtual ~RealVar(); // Destructor
};