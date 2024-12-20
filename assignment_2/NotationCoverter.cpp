// Anisha Hossain Megha (U43189731), team member: Alina Pineda Lopez (U79400432)
// NOTATION CONVERTER SOURCE FILE

/* The source file implements a notation converter for mathematical expressions, handling conversions between postfix, infix, 
and prefix notations. It uses a Dequeue class, a doubly-ended queue implemented with a doubly linked list, to manage tokens during 
conversion. The Dequeue class provides methods for checking size, accessing elements, and inserting or removing elements from 
both ends. The NotationConverter class includes helper functions to identify operators and operands, 
determine operator precedence, reverse strings, validate input strings, and split strings into tokens. 
Conversion functions handle specific transformations: postfix to infix, postfix to prefix, infix to postfix,
infix to prefix, prefix to infix, and prefix to postfix, ensuring valid expressions and throwing errors for invalid inputs.*/

#include "NotationConverterInterface.hpp" 
#include "NotationConverter.hpp"

#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

// Dequeue class constructor
template <typename E>
Dequeue<E>::Dequeue() {
    header = new Node<E>();
    trailer = new Node<E>();
    header->next = trailer;
    trailer->prev = header;
    count = 0;
}

// Dequeue class destructor
template <typename E>
Dequeue<E>::~Dequeue() {
    while (!isempty()) {
        popfront();
    }
    delete header;
    delete trailer;
}

// Dequeue class member functions declarations
template <typename E>
int Dequeue<E>::size() const {
    return count;
}


template <typename E>
bool Dequeue<E>::isempty() const {
    return count == 0;
}

template <typename E>
const E& Dequeue<E>::top() const {
    if (isempty()) {
        throw("Deque is empty");
    }
    return header->next->data;
}

template <typename E>
const E& Dequeue<E>::back() const {
    if (isempty()) {
        throw("Deque is empty");
    }
    return trailer->prev->data;
}

template <typename E>
void Dequeue<E>::insertfront(const E& e) {
    Node<E>* newNode = new Node<E>();
    newNode->data = e;
    newNode->next = header->next;
    newNode->prev = header;
    header->next->prev = newNode;
    header->next = newNode;
    count++;
}

template <typename E>
void Dequeue<E>::insertback(const E& e) {
    Node<E>* newNode = new Node<E>();
    newNode->data = e;
    newNode->prev = trailer->prev;
    newNode->next = trailer;
    trailer->prev->next = newNode;
    trailer->prev = newNode;
    count++;
}

template <typename E>
void Dequeue<E>::popfront() {
    if (isempty()) {
        throw("Deque is empty");
    }
    Node<E>* oldNode = header->next;
    header->next = oldNode->next;
    oldNode->next->prev = header;
    delete oldNode;
    count--;
}

template <typename E>
void Dequeue<E>::popback() {
    if (isempty()) {
        throw ("Deque is empty");
    }
    Node<E>* oldNode = trailer->prev;
    trailer->prev = oldNode->prev;
    oldNode->prev->next = trailer;
    delete oldNode;
    count--;
}


// Helper function to check if a token is an operator
bool NotationConverter::isOperator(const std::string &token) {
    return token == "+" || token == "-" || token == "*" || token == "/";
}

// Helper function to check if a token is an operand
bool NotationConverter::isOperand(const std::string &token) {
    if (token.length() != 1) return false;
    char c = token[0];
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '(' || c == ')';
}



// Helper function to determine the precedence of operators
int NotationConverter::precedence(const std::string &op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0;
}


// Helper function to reverse a string
void NotationConverter::reverseString(std::string &str) {
    int n = str.length();
    for (int i = 0; i < n / 2; ++i) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

//Helper function to check if input string is valid
bool NotationConverter::isInvalid(const std::string& str) {
    for (char c : str) {
        if (!isOperand(std::string(1, c)) && !isOperator(std::string(1, c)) && c != '(' && c != ')' && c != ' ') {
            return true;
        }
    }
    return false;
}

// Helper function to split strings into seperate tokens
void NotationConverter::splitString(const std::string &str, Dequeue<std::string> &tokens) {
    std::string character;
    for (char c : str) {
        if (c == ' ') {
            if (!character.empty()) {
                tokens.insertback(character);
                character.clear();
            }
        } else if (c == '(' || c == ')') {
            if (!character.empty()) {
                tokens.insertback(character);
                character.clear();
            }
            tokens.insertback(std::string(1, c));
        } else {
            character += c;
        }
    }
    if (!character.empty()) {
        tokens.insertback(character);
    }
}


// Convert postfix to infix
std::string NotationConverter::postfixToInfix(std::string inStr) {
    //throwing error if string is invalid
    if (isInvalid(inStr)) {
    throw("Invalid character in expression");
}
    Dequeue<std::string> stack; // doubly ended queue used as a stack to store token for conversion
    Dequeue<std::string> tokens;
    splitString(inStr, tokens); // splitting strings into tokens

    //conversion
    while (!tokens.isempty()) {
        std::string token = tokens.top();
        tokens.popfront();
        // Check if the current token is an operator
        if (isOperator(token)) {
            // Ensure there are at least two operands in the stack for the operator
            if (stack.size() < 2) throw("Invalid postfix expression");
            std::string op2 = stack.back(); stack.popback();
            std::string op1 = stack.back(); stack.popback();
            std::string expr = "(" + op1 + " " + token + " " + op2 + ")";
            // Push the new expression back onto the stack
            stack.insertback(expr);
        } else {
            stack.insertback(token);
        }
    }
    // After processing all tokens, there should be exactly one element in the stack
    // If not, the postfix expression was invalid
    if (stack.size() != 1) throw("Invalid postfix expression");
    // Return the final expression from the stack
    return stack.back(); //returning output
}

//convert postfix to a prefix 
std::string NotationConverter::postfixToPrefix(std::string inStr) {
    //throwing error if string is invalid
    if (isInvalid(inStr)) {
        throw("Invalid character in expression");
    }

    Dequeue<std::string> stack; // doubly ended queue used as a stack to store token for conversion
    Dequeue<std::string> tokens;
    splitString(inStr, tokens); // splitting strings into tokens

    while (!tokens.isempty()) {
        std::string token = tokens.top();
        tokens.popfront();

        // Check if the token is an operator
        if (isOperator(token)) {
            // Ensure there are at least two operands in the stack for the operator
            if (stack.size() < 2) throw("Invalid postfix expression");

            // Pop the top two operands from the stack
            std::string op2 = stack.back(); stack.popback();
            std::string op1 = stack.back(); stack.popback();

            std::string expr = token + " " + op1 + " " + op2;

            // Push the new expression back onto the stack
            stack.insertback(expr);
        } else {
            // If the token is not an operator, it must be an operand
            // Push the operand onto the stack
            stack.insertback(token);
        }
    }

    // After processing all tokens, there should be exactly one element in the stack
    // If not, the postfix expression was invalid
    if (stack.size() != 1) throw("Invalid postfix expression");

    return stack.back(); //returning output
}

std::string NotationConverter::infixToPostfix(std::string inStr) {

    //Deque that contanes the letters from A to Z
    Dequeue<char> operands;
    //Deque that contains the algorithmic operators
    Dequeue<char> operators;
    //Deque that contains the last message
    Dequeue<char> result;
    //string that has the actual last message
    std::string expression;

    for (char &ch:inStr){
        if (ch=='(' || ch==' ') continue; //passing when open bracket or whitespace
        else if ((ch<='Z'&&ch>='A')||(ch<='z'&&ch>='a')){ //if operand than inserting at fron of deque
            operands.insertfront(ch);
        }else if (ch=='+'||ch=='-'||ch=='*'||ch=='/'){
            operators.insertfront(ch);
        } else if (ch==')'){
            if (operands.size()==2){  // 2 operators
                result.insertback(operands.back());
                operands.popback();
                result.insertback(operands.back());
                operands.popback();
                result.insertback(operators.top());
                operators.popfront();
            } else if (operands.size()==1){  // 1 operator
                result.insertback(operands.top());
                operands.popback();
                result.insertback(operators.top());
                operators.popfront();
            } else if (operands.isempty()){ // only operator left
                result.insertback(operators.top());
                operators.popfront();
            }
        } else {
            //checking if character is invalid
            throw("Invalid Character");
        }
    }
    //empty the output deque into the message string
    while (!result.isempty()){
        expression+=result.top();
        expression+=" ";
        result.popfront();
    }
    return expression; //returning output
}


std::string NotationConverter::infixToPrefix(std::string inStr) {
    //Deque that contains the letters from A to Z
    Dequeue<char> operands;
    //Deque that contains the algorithmic operators
    Dequeue<char> operators;
    //Deque that contains the last message
    Dequeue<char> output;
    //string that has the actual last message
    std::string expression;
    //loop to iterate through the string
    for (char &ch:inStr){
        if (ch=='(' || ch==' ') continue;
        else if ((ch<='Z'&&ch>='A')||(ch<='z'&&ch>='a')){//insert the character in the element stack
            operands.insertfront(ch);
        }else if (ch=='+'||ch=='-'||ch=='*'||ch=='/'){//insert the operation in the operator stack
            operators.insertfront(ch);
        } else if (ch==')'){//when it finds a ')' it starts 1 on 3 options
            //option 1: there's 2 elements and an operator
            if (operands.size()==2){
                output.insertback(operators.top());
                operators.popfront();
                output.insertback(operands.back());
                operands.popback();
                output.insertback(operands.back());
                operands.popback();
            } else if (operands.size()==1){//1 element and an operator
                output.insertfront(operators.top());
                operators.popfront();
                output.insertback(operands.top());
                operands.popback();
            } else if (operands.isempty()){//there's only an operator
                output.insertfront(operators.top());
                operators.popfront();
            }
        } else {
            //checking if character is invalid
            throw("Invalid Character");
        }
    }
    //empty the output deque into the message string
    while (!output.isempty()){
        expression+=output.top();
        expression+=" ";
        output.popfront();
    }
    //return complete message
    return expression;
}



// Convert prefix to infix
std::string NotationConverter::prefixToInfix(std::string inStr) {
    if (isInvalid(inStr)) {
    //checking if string is invalid
    throw("Invalid character in expression");
}

    Dequeue<std::string> stack; // doubly ended queue used as a stack to store token for conversion
    Dequeue<std::string> tokens;
    reverseString(inStr); //Reversing input string for processing
    splitString(inStr, tokens); //splitting the string into seperate tokens

    while (!tokens.isempty()) {
        std::string token = tokens.top();
        tokens.popfront();

        if (isOperator(token)) {
            // Ensure there are at least two operands in the stack for the operator
            if (stack.size() < 2) throw("Invalid prefix expression");

            // Pop the top two operands from the stack
            std::string op1 = stack.back(); stack.popback();
            std::string op2 = stack.back(); stack.popback();
            std::string expr = "(" + op1 + " " + token + " " + op2 + ")";
            // Push the new expression back onto the stack
            stack.insertback(expr);
        } else { // If it's an operand, just push it onto the stack
            stack.insertback(token);
        }
    }
    // After processing, there should be exactly one valid expression in the stack
    if (stack.size() != 1) throw("Invalid prefix expression");
    return stack.back(); //returning the result
}

// Convert prefix to postfix
std::string NotationConverter::prefixToPostfix(std::string inStr) {
    if (isInvalid(inStr)) {
    //checking if string is invalid
    throw("Invalid character in expression");
}

    Dequeue<std::string> stack; // doubly ended queue used as a stack to store token for conversion
    Dequeue<std::string> tokens;
    reverseString(inStr); //Reversing input string for processing
    splitString(inStr, tokens); //splitting the string into seperate tokens


    while (!tokens.isempty()) {
        std::string token = tokens.top();
        tokens.popfront();

        // Check if the token is an operator
        if (isOperator(token)) {
            // Ensure there are at least two operands in the stack for the operator
            if (stack.size() < 2) throw ("Invalid prefix expression");
            // Pop the top two operands from the stack
            std::string op1 = stack.back(); stack.popback();
            std::string op2 = stack.back(); stack.popback();
            std::string expr = op1 + " " + op2 + " " + token;
            
            stack.insertback(expr);
        } else {
            stack.insertback(token);
        }
    }
    // After processing, there should be exactly one valid expression in the stack
    if (stack.size() != 1) throw ("Invalid prefix expression");
    return stack.back(); //returning the result
}

