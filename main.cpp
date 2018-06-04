#include "forward.h"
#include "reverse.h"
using std::cout; using std::endl;


fRev function(fRev f1, fRev f2, fRev f3)
{
    return sin(7 + 2 * f1 * f2  / f3);
}

fFwd function2(fFwd f)
{
    fFwd a = f * f;
    fFwd b = 7 / f;
    fFwd c = a + b;
    return c;
}

int main()
{
    
    // FORWARD
    
    cout << "testing forward mode." << endl << endl;

   
   fFwd x(1.2,1.0);
   fFwd a = cos(x*x + 6.0);
   fFwd b = exp(x*x*x*3.0) + x;
   fFwd cf = a * (a + b);
   
   cout << "c.value      = " << cf << "    (expected 72.4053)" << endl;
   cout << "c.derivative = " << cf.derivative() << "     (expected 534.037)" << endl;
   
   cout << "\n forward mode test2." << endl;
   
   fFwd s = 3.0;
   s.setDerivative(1.0);
   fFwd g = function2(s);
   cout << "g.value      = " << g << "     expected 11.3333" << endl;
   cout << "g.derivative = " << g.derivative() << "   expected 5.2222" << endl;
    
    // REVERSE
   
   cout << "\ntesting the reverse mode." << endl << endl;

    reverseAD::initTape();
    fRev f1 = 6.0;
    fRev f2 = 3.0;
    fRev f3 = 2.0;
    
    //fRev c = sin(f1 * f2 / f3);
    fRev c = function(f1,f2,f3);
    reverseAD::evaluateTape(c);
    cout << "f1.derivative = " << f1.derivative() << "   expected: 2.9736." << endl;
    cout << "f2.derivative = " << f2.derivative() << "   expected: 5.9472." << endl;
    cout << "f3.derivative = " << f3.derivative() << "   expected: -8.9208." << endl;
    
    cout << "tapeSize = " << reverseAD::tapeSize() << endl;
}
