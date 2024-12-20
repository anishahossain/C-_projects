// Anisha Hossain Megha (U43189731), team member: Alina Pineda Lopez (U79400432)
// CALC LIST SOURCE FILE

#include "CalcList.hpp" //Including CalcList header file
#include "CalcListInterface.hpp" //Including CalcListInterface header file

CalcList::CalcList() : stack() {}  // Calclist Constructor 

// returns current total
double CalcList :: total() const{
    if (stack.isempty()) {
        return 0.0;
    }
    return stack.top();
}

// performs new operation on total and pushes new total to stack
void CalcList :: newOperation(const FUNCTIONS func, const double operand){

    double c_total = total();

    switch (func) {
        case NONE:
            break;
        case ADDITION:
            c_total += operand;
            break;
        case SUBTRACTION:
            c_total -= operand;
            break;
        case MULTIPLICATION:
            c_total *= operand;
            break;
        case DIVISION:
            if (operand == 0) {
                throw ("Cannot divide by zero");
            }
            c_total /= operand;
            break;
    }
    stack.stackpush(c_total, func, operand);
}

// removes last operation from stack so last operation on total is undone
void CalcList :: removeLastOperation(){
    stack.stackpop();
}

std::string CalcList::toString(unsigned short precision) const {
    std::ostringstream oss;
    Node<double>* current = stack.topnode;

    int step = stack.size(); // number of steps for operations- number of stack members
    double previousTotal = 0.0; // Start with 0.0 as the initial total

    while (current != nullptr) {
        // Calculate the previous total before the current operation
        switch (current->func) {
            case NONE:
                break;
            case ADDITION:
                previousTotal = current->data - current->operand;
                break;
            case SUBTRACTION:
                previousTotal = current->data + current->operand;
                break;
            case MULTIPLICATION:
                previousTotal = current->data / current->operand;
                break;
            case DIVISION:
                previousTotal = current->data * current->operand;
                break;
        }

        oss << step << ": " << std::fixed << std::setprecision(precision) << previousTotal;

        switch (current->func) {
            case NONE:
                break;
            case ADDITION:
                oss << "+";
                break;
            case SUBTRACTION:
                oss << "-";
                break;
            case MULTIPLICATION:
                oss << "*";
                break;
            case DIVISION:
                oss << "/";
                break;
        }

        oss << std::fixed << std::setprecision(precision) << current->operand << "=" << current->data << "\n";
        current = current->next;
        step--; // decrementing steps
        //currently shows every operation step to precision
    }

    return oss.str();
}
