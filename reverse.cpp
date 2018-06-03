/* 
 * File:   reverse.h
 * Author: benno
 *
 * Created on June 3, 2018, 4:12 PM
 */
    
#include "reverse.h"
#include <assert.h>
// ---------------------------------------------- reverse AD

namespace reverseAD
{

int addToTape(Node* n)
{
    assert(index_ < TAPE_SIZE);
    tape_[index_] = n;
    index_++;
    return index_ - 1;
}

void initTape()
{
    index_ = 0;
    tape_.resize(TAPE_SIZE);
}
    
void resetTape()
{
    for(int i = 0; i < index_; i++)
    {
        delete tape_[i];
    }
    index_ = 0;
}

void evaluateTape(const fRev& fR)
{
    Node& start = *(globalTape()[fR.index()]);
    start.setDerivative(1.0);
}

void evaluateTapeRecursively(Node& n)
{
    int parent1 = n.getParentNode1();
    int parent2 = n.getParentNode2();
    Operation op = n.getOperation();
    switch(op)
    {
        case Operation::addition:
            reverseAddition(n, parent1, parent2);
            break;
        case Operation::multiplication:
            reverseMultiplication(n, parent1, parent2);
            break;
        case Operation::assignment:
            reverseAssignment(n, parent1);
            assert(parent2 == -1);
            break;
        case Operation::copy:
            reverseCopy(n, parent1);
            assert(parent2 == -1);
            break;
        case Operation::none:
            break;
        default:
            assert(false);
    }
    if(parent1 != -1)
        evaluateTapeRecursively((*globalTape()[parent1]));
    if(parent2 != -1)
        evaluateTapeRecursively((*globalTape()[parent2]));
}

void reverseAddition(Node& n, int parentIndex1, int parentIndex2)
{
    Node& parent1 = (*globalTape()[parentIndex1]);
    Node& parent2 = (*globalTape()[parentIndex2]);
    parent1.setDerivative(parent1.getDerivative() + n.getDerivative());
    parent2.setDerivative(parent2.getDerivative() + n.getDerivative());
}

void reverseMultiplication(Node& n, int parentIndex1, int parentIndex2)
{
    Node& parent1 = (*globalTape()[parentIndex1]);
    Node& parent2 = (*globalTape()[parentIndex2]);
    parent1.setDerivative(parent1.getDerivative() + n.getDerivative() * parent2.getValue());
    parent2.setDerivative(parent2.getDerivative() + n.getDerivative() * parent1.getValue());
}

void reverseAssignment(Node& n, int parentIndex)
{
    Node& parent = (*globalTape()[parentIndex]);
    parent.setDerivative(n.getDerivative());
    n.setDerivative(0.0);
}

void reverseCopy(Node& n, int parentIndex)
{
    Node& parent = (*globalTape()[parentIndex]);
    parent.setDerivative(parent.getDerivative() + n.getDerivative());
}

} // namespace reverseAD

// --------------------------------------------- fRev

fRev::fRev()
{
    Node* n = new Node(0.0, 0.0, -1, -1, Operation::none);
    index_ = reverseAD::addToTape(n);
}

fRev::fRev(const fRev& fr)
{
    Node* n = new Node(fr.value(), 0.0, fr.index_, -1, Operation::copy);
    index_ = reverseAD::addToTape(n);
}

fRev::fRev(int i)
{
    index_ = i;
}

double fRev::value() const
{
    return reverseAD::globalTape()[index_]->getValue();
}

double fRev::derivative() const
{
    return reverseAD::globalTape()[index_]->getDerivative();
}

fRev& fRev::operator=(const fRev& fR) 
{
    double value = reverseAD::globalTape()[fR.index_]->getValue();
    Node* n = new Node(value , 0.0, fR.index_, -1, Operation::assignment);
    index_ = reverseAD::addToTape(n);
    return *this;
}



//fRev& fRev::operator=(double d) 
//{
//    Node* n = new Node(d, 0.0, -1, -1, Operation::none);
//    index_ = reverseAD::addToTape(n);
//    return *this;
//}


fRev fRev::operator+(const fRev& fR) const 
{
    double v = value() + fR.value();
    Node* n = new Node(v, 0.0, this->index_, fR.index_, Operation::addition);
    int index = reverseAD::addToTape(n);
    return fRev(index);
}

// --------------------------------------------- Node

Node::Node(double v, double d, int p1, int p2, Operation op)
{
    value_ = v;
    derivative_ = d;
    parent1_ = p1;
    parent2_ = p2;
    op_ = op;
}