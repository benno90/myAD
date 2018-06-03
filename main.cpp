#include "forward.h"
#include "reverse.h"
using std::cout; using std::endl;


fRev function(fRev f1, fRev f2, fRev f3)
{
    return sin(f1 * f2 / f3);
}

int main()
{
    
    // FORWARD
    
    /*
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
   */
    
    // REVERSE

    reverseAD::initTape();
    fRev f1(6.0);
    fRev f2(3.0);
    fRev f3(2.0);
    
    //fRev c = sin(f1 * f2 / f3);
    fRev c = function(f1,f2,f3);
    reverseAD::evaluateTape(c);
    cout << "f1.derivative = " << f1.derivative() << endl;
    cout << "f2.derivative = " << f2.derivative() << endl;
    cout << "f3.derivative = " << f3.derivative() << endl;
    
    cout << "tapeSize = " << reverseAD::tapeSize() << endl;
}
