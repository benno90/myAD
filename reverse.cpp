/* 
 * File:   reverse.h
 * Author: benno
 *
 * Created on June 3, 2018, 4:12 PM
 */
    
#include "reverse.h"
#include <assert.h>
#include <cmath>


// ----------------------------------------------------------------------------- reverse AD


// definition of the static members
    Tape reverseAD::tape_ = Tape(reverseAD::TAPE_SIZE);
    int reverseAD::index_ = 0;
    bool reverseAD::recording_ = false;

int reverseAD::addToTape(Node* n)
{
    assert(index_ < TAPE_SIZE);
    tape_[index_] = n;
    index_++;
    return index_ - 1;
}

Node& reverseAD::getNode(int index)
{
    assert(index < index_);
    return *(tape_[index]);
}

void reverseAD::initTape()
{
    index_ = 0;
    tape_.resize(TAPE_SIZE);
}
    
void reverseAD::resetTape()
{
    for(int i = 0; i < index_; i++)
    {
        delete tape_[i];
    }
    index_ = 0;
}

void reverseAD::evaluateTape(const fRev& fR)
{
    Node& start = *(globalTape()[fR.index()]);
    start.setDerivative(1.0);
    evaluateTapeRecursively(start);
}

void reverseAD::evaluateTapeRecursively(Node& n)
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
        case Operation::division:
            reverseDivision(n, parent1, parent2);
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
            assert(parent1 == -1);
            assert(parent2 == -1);
            break;
        case Operation::sin:
            reverseSin(n, parent1);
            break;
        default:
            assert(false);
    }
    if(parent1 != -1)
        evaluateTapeRecursively(reverseAD::getNode(parent1));
    if(parent2 != -1)
        evaluateTapeRecursively(reverseAD::getNode(parent2));
}

void reverseAD::reverseAddition(Node& n, int parentIndex1, int parentIndex2)
{
    Node& parent1 = reverseAD::getNode(parentIndex1); 
    Node& parent2 = reverseAD::getNode(parentIndex2);
    parent1.incrementDerivative(n.getDerivative());
    parent2.incrementDerivative(n.getDerivative());
}

void reverseAD::reverseMultiplication(Node& n, int parentIndex1, int parentIndex2)
{
    Node& parent1 = reverseAD::getNode(parentIndex1);
    Node& parent2 = reverseAD::getNode(parentIndex2);
    parent1.incrementDerivative(n.getDerivative() * parent2.getValue());
    parent2.incrementDerivative(n.getDerivative() * parent1.getValue());
}

void reverseAD::reverseDivision(Node& n, int parentIndex1, int parentIndex2)
{
    Node& parent1 = reverseAD::getNode(parentIndex1);
    Node& parent2 = reverseAD::getNode(parentIndex2);
    parent1.incrementDerivative(n.getDerivative() / parent2.getValue());
    parent2.incrementDerivative(-n.getDerivative() * parent1.getValue() / (parent2.getValue() * parent2.getValue()));
}

void reverseAD::reverseAssignment(Node& n, int parentIndex)
{
    Node& parent = reverseAD::getNode(parentIndex);
    parent.setDerivative(n.getDerivative());
    n.setDerivative(0.0);
}

void reverseAD::reverseCopy(Node& n, int parentIndex)
{
    Node& parent = reverseAD::getNode(parentIndex);
    parent.incrementDerivative(n.getDerivative());
}

void reverseAD::reverseSin(Node& n, int parentIndex)
{
    Node& parent = reverseAD::getNode(parentIndex);
    parent.incrementDerivative(std::cos(parent.getValue())*n.getDerivative());
}



// ----------------------------------------------------------------------------- fRev

fRev::fRev()
{
    Node* n = new Node(0.0, 0.0, -1, -1, Operation::none);
    index_ = reverseAD::addToTape(n);
}

fRev::fRev(double v)
{
    Node* n = new Node(v, 0.0, -1, -1, Operation::none);
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

fRev fRev::operator*(const fRev& fR) const
{
    double v = value() * fR.value();
    Node* n = new Node(v, 0.0, this->index_, fR.index_, Operation::multiplication);
    int index = reverseAD::addToTape(n);
    return fRev(index);
}

fRev fRev::operator/(const fRev& fR) const
{
    double v = value() / fR.value();
    Node* n = new Node(v, 0.0, this->index_, fR.index_, Operation::division);
    int index = reverseAD::addToTape(n);
    return fRev(index);
}


fRev sin(const fRev& fR)
{
    double v = std::sin(fR.value());
    Node* n = new Node(v, 0.0, fR.index(), -1, Operation::sin);
    int index = reverseAD::addToTape(n);
    return fRev(index);
}

// ----------------------------------------------------------------------------- Node

Node::Node(double v, double d, int p1, int p2, Operation op)
{
    value_ = v;
    derivative_ = d;
    parent1_ = p1;
    parent2_ = p2;
    op_ = op;
}