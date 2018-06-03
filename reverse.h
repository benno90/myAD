/* 
 * File:   reverse.h
 * Author: benno
 *
 * Created on June 3, 2018, 3:58 PM
 */

#ifndef REVERSE_H
#define REVERSE_H

#include <vector>

class Node;
class fRev;

using Tape = std::vector<Node*>;

enum class Operation
{
    none,
    assignment,
    copy,
    addition,
    multiplication,
    division,
    sin,
    cos,
    exp
};

class reverseAD
{
private:
    // members
    static Tape tape_;
    static int index_;
    static bool recording_;
    static const int TAPE_SIZE = 100;
public:
    // functions
    static int addToTape(Node* n);
    static void resetTape();
    static void initTape();
    static Tape& globalTape() {return tape_;}
    
    static void evaluateTape(const fRev& fR);

    
    static int tapeSize() {return index_;}
    
private:
    static void evaluateTapeRecursively(Node& n);
    
    // reverse methods
    static void reverseAddition(Node& n, int parentIndex1, int parentIndex2);
    static void reverseMultiplication(Node& n, int parent1, int parent2);
    static void reverseDivision(Node& n, int parentIndex1, int parentIndex2);
    static void reverseAssignment(Node& n, int parentIndex);
    static void reverseCopy(Node& n, int parentIndex);
    static void reverseSin(Node& n, int parentIndex);
    

};


class fRev
{
public:
    fRev();
    fRev(int i);
    fRev(double v);
    fRev(const fRev& fr);
    //fRev(fRev& fr);
    
    double value() const;
    double derivative() const;
    int index() const {return index_;}
    
    fRev& operator=(const fRev& fR);
    //fRev& operator=(double d);
    
    fRev operator+(const fRev& fR) const;
    fRev operator*(const fRev& fR) const;
    fRev operator/(const fRev& fR) const;
private:
    int index_;
};


// external functions
fRev sin(const fRev& fR);

class Node
{
public:
    Node(double v, double d, int p1, int p2, Operation op);
    double getValue() const {return value_;}
    double getDerivative() const {return derivative_;}
    int getParentNode1() const {return parent1_;}
    int getParentNode2() const {return parent2_;}
    Operation getOperation() const {return op_;}
    void setDerivative(double d) {derivative_ = d;}
private:
    int parent1_;
    int parent2_;
    double value_;
    double derivative_ = 0.0;
    Operation op_;
};

#endif /* REVERSE_H */

