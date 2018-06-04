/* 
 * File:   reverse.h
 * Author: benno
 *
 * Created on June 2, 2018, 20:58 PM
 */

#include <iostream>
#include <cmath>

#ifndef FLOAT_FORWARD__
#define FLOAT_FORWARD__
class fFwd
{
public:
   fFwd() {val_ = 0.0; der_ = 0.0;}
   fFwd(const fFwd& fF) {val_ = fF.val_; der_ = fF.der_;}
   fFwd(double v) {val_ = v; der_ = 0.0;}
   fFwd(double v, double d) {val_ = v; der_ = d;}
   double value() const {return val_;}
   double derivative() const {return der_;}
   void setValue(double v) {val_ = v;}
   void setDerivative(double d) {der_ = d;}
   
   fFwd& operator=(const fFwd& fF) {val_ = fF.val_; der_ = fF.der_; return *this;}
   fFwd& operator=(double d) {val_ = d; der_ = 0.0; return *this;}
   
   // addition
   fFwd operator+(const fFwd& fF) const {return fFwd(val_ + fF.val_, der_ + fF.der_);}
   fFwd operator+(double d) const {return fFwd(val_ + d, der_);}
   friend fFwd operator+(double d, const fFwd& fF) {return fFwd(fF.val_ + d, fF.der_);}
   
   // multiplication
   fFwd operator*(const fFwd& fF) const {return fFwd(val_ * fF.val_, fF.val_ * der_ + val_ * fF.der_);}
   fFwd operator*(double d) const {return fFwd(val_ * d, der_ * d);}
   friend fFwd operator*(double d, const fFwd& fF) {return fFwd(fF.val_ * d, d * fF.der_);}
   
   // division
   fFwd operator/(const fFwd& fF) const {return fFwd(val_ / fF.val_, der_ / fF.val_  - fF.der_ * val_ / (fF.val_ * fF.val_));}
   fFwd operator/(double d) const {return fFwd(val_ / d, der_ / d);}
   friend fFwd operator/(double d, const fFwd& fF) {return fFwd(d / fF.val_, -d / (fF.val_ * fF.val_) * fF.der_);}
   
   friend std::ostream& operator << (std::ostream& os, const fFwd& fF) {os << fF.value(); return os;}
private:
   double val_;
   double der_;
};

fFwd sin(const fFwd& fF) {return fFwd(std::sin(fF.value()), std::cos(fF.value()) * fF.derivative());}
fFwd cos(const fFwd& fF) {return fFwd(std::cos(fF.value()), -std::sin(fF.value()) * fF.derivative());}
fFwd exp(const fFwd& fF) {return fFwd(std::exp(fF.value()), std::exp(fF.value()) * fF.derivative());}


#endif