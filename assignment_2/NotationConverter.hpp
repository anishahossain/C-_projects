// Anisha Hossain Megha (U43189731), team member: Alina Pineda Lopez (U79400432)
// NOTATION CONVERTER HEADER FILE

/*The header file defines functionality for converting mathematical expressions between postfix, infix, and prefix notations. 
It includes a class for managing a doubly-ended queue using a doubly linked list, with methods for checking size, accessing elements,
and inserting or removing elements from both ends. Another class provides methods for converting between notations 
and includes helper functions to identify operators and operands, determine precedence, and manipulate strings. 
This setup is essential for implementing a versatile notation converter for different mathematical expression formats.*/


#ifndef NOTATIONCONVERTER_H
#define NOTATIONCONVERTER_H

#include <string>

// Class Node for doubly linked list queue
template <typename E>
class Node {
public:
    Node() {}
private:
    E data;    // Value of the node
    Node<E>* next;  // Pointer to the next node
    Node<E>* prev; // Pointer to previous node

    //friend classes
    template <typename T>
    friend class Dequeue;

    friend class NotationConverter;
};

template <typename E>
// doubly ended queue class
class Dequeue {
    public:
        Dequeue(); // constructor for doubly ended queue
        ~Dequeue(); // destructor for doubly ended queue
        int size() const; // number of items in stack
        bool isempty() const; // returns true if queue is empty
        const E& top() const; // returns first node value
        const E& back() const; // returns last node value

        void insertfront(const E& e); //adding to front of list
        void insertback(const E& e); //adding to back of list
        void popfront(); // pops first node
        void popback(); //pops last node
    private:
        //sentinel nodes 
        Node<E>* header;
        Node<E>* trailer;
        int count; // number of items in list

        friend class NotationConverter;
};

class NotationConverter : public NotationConverterInterface {
public:
    std::string postfixToInfix(std::string inStr) override;
    std::string postfixToPrefix(std::string inStr) override;
    std::string infixToPostfix(std::string inStr) override;
    std::string infixToPrefix(std::string inStr) override;
    std::string prefixToInfix(std::string inStr) override;
    std::string prefixToPostfix(std::string inStr) override;

private: //helper functions
    bool isOperator(const std::string &token); // Checks if a given token is an operator
    bool isOperand(const std::string &token); // Checks if a given token is an operand
    int precedence(const std::string &op); // Returns the precedence of a given operator
    void reverseString(std::string &str); // Reverses a given string
    void splitString(const std::string &str, Dequeue<std::string> &tokens); // Splits a string into tokens and stores them in a queue
    bool isInvalid(const std::string& str); // Checks if the input string contains any invalid characters
};


#endif /* NOTATIONCONVERTER_H */