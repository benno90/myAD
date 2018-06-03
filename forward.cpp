#include "forward.h"


//floatForward::floatForward()
//{
//   value_ = 0.0;
//   derivative_ = 0.0;
//}


//floatForward::floatForward(const floatForward& fF)
//{
//   value_ = fF.getValue();
//   derivative_ = fF.getDerivative();
//}

//floatForward::floatForward(double v)
//{
//   value_ = v;
//}

//floatForward::floatForward(double v, double d)
//{
//   value_ = v;
//   derivative_ = d;
//}

//inline double floatForward::getValue() const
//{
//   return value_;
//}

//inline double floatForward::getDerivative() const
//{
//   return derivative_;
//}
   
//inline void floatForward::setValue(double v)
//{
//   value_ = v;
//}

//inline void floatForward::setDerivative(double d)
//{
//   derivative_ = d;
//}

//floatForward& floatForward::operator=(const floatForward& fF)
//{
//   value_ = fF.value_;
//   derivative_ = fF.derivative_;
//}

//floatForward& floatForward::operator=(double d)
//{
//   value_ = d;
//   derivative_ = 0.0;
//}


//floatForward floatForward::operator+(const floatForward& fF) const
//{
//   return floatForward(value_ + fF.value_, derivative_ + fF.derivative_);
//   //return newF;
//}

//floatForward floatForward::operator+(double d) const
//{
//   floatForward newF(value_ + d, derivative_);
//   return newF;
//}

//floatForward operator+(double d, const floatForward& fF)
//{
//   floatForward newF(fF.value_ + d, fF.derivative_);
//   return newF;
//}



//floatForward floatForward::operator*(const floatForward& fF) const
//{
//   floatForward newF(value_ * fF.value_, fF.value_ * derivative_ + value_ * fF.derivative_);
//   return newF;
//}

//floatForward floatForward::operator*(double d) const
//{
//   floatForward newF(value_ * d, derivative_ * d);
//   return newF;
//}

//floatForward operator*(double d, const floatForward& fF)
//{
//   floatForward newF(fF.value_ * d, d * fF.derivative_);
//   return newF;
//}






//std::ostream& operator << (std::ostream& os, const floatForward& fF)
//{
//   os << fF.getValue();
//   return os;
//}




//floatForward sin(const floatForward& fF)
//{
//    floatForward newF(std::sin(fF.getValue()), std::cos(fF.getValue()) * fF.getDerivative());
//    return newF;
//}
