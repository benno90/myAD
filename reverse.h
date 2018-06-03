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
    addition,
    multiplication,
    assignment,
    copy,
    none,
};

namespace reverseAD
{
    static Tape tape_;
    static int index_;
    static bool recording_;
    static const int TAPE_SIZE = 100;
    
    int addToTape(Node* n);
    void resetTape();
    void initTape();
    static Tape& globalTape() {return tape_;}
    
    void evaluateTape(const fRev& fR);
    void evaluateTapeRecursively(Node& n);
    
    // reverse methods
    void reverseAddition(Node& n, int parentIndex);
    void reverseAssignment(Node& n, int parentIndex);
    void reverseCopy(Node& n, int parentIndex);
    

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
private:
    int index_;
};

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

