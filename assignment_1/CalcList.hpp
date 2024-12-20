// Anisha Hossain Megha (U43189731), team member: Alina Pineda Lopez (U79400432)
// CALC LIST HEADER FILE

#ifndef CALCLIST_H
#define CALCLIST_H
#include "CalcListInterface.hpp" //Including CalcListInterface header file

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>


// Class Node for singly linked list Stack 
template <typename E>
class Node {
public:
    Node() {}
private:
    E data;    // Value of the node
    double operand; // value of operand 
    FUNCTIONS func; // func enum 
    Node<E>* next;  // Pointer to the next node

    template <typename T>
    friend class Stack;

    friend class CalcList;
};

template <typename E>
// stack class
class Stack {
    public:
        Stack(); // constructor for stack
        ~Stack(); // destructor for stack
        int size() const; // number of items in stack
        bool isempty() const; // returns true if stack is empty
        const E& top() const; // returns top element
        void stackpush(const E& e, const FUNCTIONS func, const double operand); // push element
        void stackpop(); // pop element
    private:
        Node<E>* topnode;
        int count; // number of items in list

        friend class CalcList;
};

// Stack Class constructor
template <typename E>
Stack<E> :: Stack(){ 
    topnode = nullptr; //stack is empty, topnode is pointing to NULL
    count = 0; //count starts at 0
}

// destructor - deallocating memory at the end from stack
template <typename E> 
Stack<E> :: ~Stack(){
    Node<E>* temp = topnode;
    while (!isempty()) {
        topnode = topnode->next;
        delete temp;
        temp = topnode;
        count--;
    }
}

// returns size of current stack
template <typename E>
int Stack<E> :: size() const {
    return count;
}

// returns true if stack is empty
template <typename E>
bool Stack<E> :: isempty() const {
    return count == 0;
}

// returns top element if list is not empty
template <typename E>
const E& Stack<E>::top() const {
    if (isempty()) {
        throw ("List is empty");
    }
    return topnode->data;
}

// pushes element onto stack
template <typename E>
void Stack<E>::stackpush(const E& e, const FUNCTIONS func, const double operand) {
    Node<E> *temp = new Node<E>;
    temp->func = func; // current operation 
    temp->operand = operand; // current operand
    temp->data = e; // e is the current total
    temp->next = topnode;
    topnode = temp; // LIFO - new element added is the new top
    count++; // incrementing count
}

// pops element from stack
template <typename E>
void Stack<E>::stackpop(){
    //checking if stack is empty
    if (isempty()) {
        throw ("Cannot remove last operation as list is empty");
    }
    Node<E> *temp = topnode;
    topnode = topnode->next;
    delete temp; //deallocating node
    count--; //decrementing count
}

//derived class from Abstract class for making objects and executing functions
class CalcList : public CalcListInterface {
public:
    CalcList();
    //over riding base class virtual functions
    double total() const override; //returns the current total
    void newOperation(const FUNCTIONS func, const double operand) override; //performs new operation
    void removeLastOperation() override; // undos last operation
    std::string toString(unsigned short precision) const override; //prints in string the operations to pricision
private:
    Stack<double> stack; // stack for Calc List object operations 
};

#endif //CALCLIST_H 