#include "forward.h"
using std::cout; using std::endl;

int main()
{
    
    
    fFwd f1(0.9, 1.0);
    //fFwd f2 = exp(f1);
    //fFwd f2 = exp(f1 * f1);
    fFwd f2 = cos(f1);
    
    
    cout << f2 << endl;
    cout << f2.derivative() << endl;
    


   //fFwd a = 2.0; a.setDerivative(1.0);
   //fFwd b = a * a * a;
   //cout << b << endl;
   //cout << b.derivative() << endl;
   
   cout << "----------------------" << endl;
   
   fFwd x(1.2,1.0);
   fFwd a = cos(x*x + 6.0);
   fFwd b = exp(x*x*x*3.0) + x;
   fFwd c = a * (a + b);
   
   cout << "c.value      = " << c << "    (expected 72.4053)" << endl;
   cout << "c.derivative = " << c.derivative() << "     (expected 534.037)" << endl;
   


}
