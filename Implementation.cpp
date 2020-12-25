// This program was made by Bannikov Nikita, group 9309 
#include "Header.h"
#include <iomanip>
#include <iostream>

using namespace std;

/*
 * Stack methods
 */
void OpStack::push(Op* newnode) {
    newnode->next = head;
    head = newnode;
    length += 1;
}

void OpStack::push(std::string* data_val, OpType type_val, int position_val) {
    push(new Op(data_val, type_val, position_val));
}

void OpStack::push(char c, OpType type_val, int position_val) {
    push (new Op(c, type_val, position_val));
}

Op* OpStack::pop() {
    if (isEmpty()) {
        return NULL;
    }
    Op* op = head;
    head = head->next;
    op->next = NULL;
    length -= 1;
    return op;
}

Op* OpStack::peek() {
    if (isEmpty()) {
        return NULL;
    }
    return head;
}

void OpStack::printStack() {
    Op* iNode = head;
    int i = 0;
    for (; i < length; i++) {
        std::cout << iNode->data << " ";
        iNode = iNode->next;
    }
    std::cout << std::endl;
}

bool OpStack::isEmpty() {
    if (head == NULL) return true;
    else return false;
}


/*
 * Covertor/Calculator methods
 */
bool InfixToPrefixCovertorAndCalculator::isOperator(char c) {
    return (c == '*' || c == '+' || c == '-' || c == '/' || c == '^');
}

int InfixToPrefixCovertorAndCalculator::stackOperatorPriority(Op* op) {
    switch (op->data->at(0))
    {
    case '+':
    case '-':
        return 1;
        break;
    case '*':
    case '/':
        return 3;
        break;
    case '^':
        return 6;
        break;
        return 0;
        break;
    }
}

int InfixToPrefixCovertorAndCalculator::currentOperatorPriority(Op* op) {
    switch (op->data->at(0)) {
    case '+':
    case '-':
        return 2;
        break;
    case '*':
    case '/':
        return 4;
        break;
    case '^':
        return 5;
        break;
        return 0;
        break;
    }
}

bool InfixToPrefixCovertorAndCalculator::isBracket(char c) {
    return (c == '(' || c == ')');
}

static void setDoubleValue(Op* op) {
    try {
        char* stopstring;
        double x = strtod(op->data->c_str(), &stopstring);
        if (strlen(stopstring) == 0) {
            op->double_val = x;
            return;
        }
    }
    catch (const std::invalid_argument& e) {
    }
    throw FormatError("Can not covert operand to double ", op->position);
}

Op* InfixToPrefixCovertorAndCalculator::getDoubleTypeOfConstant(Op* constant_op) {
    Op* op = new Op;
    if (constant_op->data->compare("pi") == 0) {
        op->data = new std::string("3.14159");
    }
    else { // e
        op->data = new std::string("2.7183");
    }
    op->type = OpType::OperandDouble;
    op->position = constant_op->position;
    return op;
}

OpType InfixToPrefixCovertorAndCalculator::getOpType(std::string op) {
    // Double operands
    try {
        //double val = std::stod(op);
        char *stopstring;
        double x = strtod(op.c_str(), &stopstring);
        if (strlen(stopstring) == 0) {
            return OpType::OperandDouble;
        }
    }
    catch (...) {
    }

    // Constants
    if (op.compare("pi") == 0) {
        return OpType::Constant;
    }

    if (op.compare("e") == 0) {
        return OpType::Constant;
    }

    // Functions
    if (op.compare("cos") == 0) {
        return OpType::Function;
    }

    if (op.compare("sin") == 0) {
        return OpType::Function;
    }

    if (op.compare("tg") == 0) {
        return OpType::Function;
    }

    if (op.compare("ctg") == 0) {
        return OpType::Function;
    }

    if (op.compare("ln") == 0) {
        return OpType::Function;
    }

    if (op.compare("log") == 0) {
        return OpType::Function;
    }

    if (op.compare("sqrt") == 0) {
        return OpType::Function;
    }

    if (op.compare("abs") == 0) {
        return OpType::Function;
    }

    return OpType::Unknown;
}

bool InfixToPrefixCovertorAndCalculator::isSeparator(char c) {
    return (c == ' ');
}

ConversionAndCalculationResult* InfixToPrefixCovertorAndCalculator::calculate(std::string* infix_str) {
    if (infix_str == NULL || infix_str->empty()) {
        throw std::invalid_argument("infix string is invalid");
    }

    clean();
    infix = infix_str;
    prefix = new std::string;
    prefix_stack = new OpStack();
    op_stack = new OpStack();
    ex_stack = new OpStack();

    ConversionAndCalculationResult* result;
    try {
        result = _convert_and_calculate();
    }
    catch (const std::exception& e) {
        result = new ConversionAndCalculationResult(NULL, false, NULL, 0.0, new std::string(e.what()));
    }
    return result;
}

ConversionAndCalculationResult* InfixToPrefixCovertorAndCalculator::_convert_and_calculate() {
    int infix_position = infix->size() - 1;
    std::string op = "";

    for (; infix_position >= 0; infix_position--) {
        char c = infix->at(infix_position);
        
        Op* delimiter = NULL;
        
        if (isOperator(c)) {
            delimiter = new Op(c, OpType::BinaryOperator, infix_position);
        }
        else if (isBracket(c)) {
            delimiter = new Op(c, OpType::Bracket, infix_position);
        }
        else if (isSeparator(c)) {
        }
        else {
            op.insert(0, 1, c);
            continue;
        }

        if (op.size() != 0) {
            OpType type = getOpType(op);
            if (type == OpType::OperandDouble) {
                /* Unary operation */
                bool isUnary = false;
                if (delimiter != NULL && delimiter->type == OpType::BinaryOperator && delimiter->data->compare("-") == 0) {
                    isUnary = true;
                    bool wasSeparator = false;
                    for (int upos = infix_position - 1; upos >= 0; upos--) {
                        char uc = infix->at(upos);
                        if (isSeparator(uc)) {
                            wasSeparator = true;
                            continue;
                        }
                        if (uc == '(' || (isOperator(uc) && wasSeparator)) {
                            break;
                        }
                        isUnary = false;
                        break;
                    }
                }

                if (isUnary) {
                    op.insert(0, 1, '-');
                    delete delimiter;
                    delimiter = NULL;
                }
                prefix_stack->push(new std::string(op), OpType::OperandDouble, infix_position + 1);
            }
            else if (type == OpType::Constant) {
                prefix_stack->push(new std::string(op), OpType::Constant, infix_position + 1);
            }
            else if (type == OpType::Function) {
                prefix_stack->push(new std::string(op), OpType::Function, infix_position + 1);
            }
            else {
                throw FormatError("Invalid operand", infix_position + 1);
            }
            op.clear();
        }
        
        if (delimiter != NULL) {
            if (delimiter->type == OpType::BinaryOperator) {
                while (!op_stack->isEmpty() &&
                    !(op_stack->peek()->type == OpType::Bracket && op_stack->peek()->data->compare(")") == 0) &&
                    (stackOperatorPriority(op_stack->peek()) > currentOperatorPriority(delimiter))) {
                    prefix_stack->push(op_stack->pop());
                }
                op_stack->push(delimiter);
            }
            else if (delimiter->type == OpType::Bracket) {
                if (delimiter->data->compare(")") == 0) {
                    op_stack->push(delimiter);
                }
                else if (delimiter->data->compare("(") == 0) {
                    bool closeBracketFound = false;
                    while (!op_stack->isEmpty()) {
                        if (op_stack->peek()->type == OpType::Bracket && op_stack->peek()->data->compare(")") == 0) {
                            op_stack->pop();
                            closeBracketFound = true;
                            break;
                        }

                        // There were no pushes: 
                        // if (op_stack->peek()->type == OpType::Bracket && op_stack->peek()->data->compare("(") == 0) {
                        //	continue;
                        //}

                        prefix_stack->push(op_stack->pop());
                    }
                    if (!closeBracketFound) {
                        throw FormatError("Close bracket not found", delimiter->position);
                    }
                    delete delimiter;
                }
            }
        }
    }

    if (op.size() != 0) {
        OpType type = getOpType(op);
        if (type == OpType::OperandDouble) {
            prefix_stack->push(new std::string(op), OpType::OperandDouble, 0);
        }
        else if (type == OpType::Constant) {
            prefix_stack->push(new std::string(op), OpType::Constant, 0);
        }
        else if (type == OpType::Function) {
            prefix_stack->push(new std::string(op), OpType::Function, 0);
        }
        else {
            throw FormatError("Invalid operand", 0);
        }
        op.clear();
    }

    /* Pop rest from stack */
    while (!op_stack->isEmpty()) {
        Op* sop = op_stack->pop();
        if (sop->type == OpType::BinaryOperator) {
            prefix_stack->push(sop);
        }
        else if (sop->type == OpType::Bracket) {
            if (sop->data->compare("(") == 0) {
                // There were no pushes: Shall not be thrown
                throw FormatError("Close bracket not found", sop->position);
            }
            else {
                throw FormatError("Open bracket not found", sop->position);
            }
        }
        else {
            std::string* err = new std::string("Runtime error: Conversion: OpStack has unexpected elements. Position: ");
            err->append(std::to_string(sop->position));
            err->append(", Type: ");
            err->append(std::to_string(sop->type));
            err->append(", Data: ");
            err->append(*(sop->data));
            return new ConversionAndCalculationResult(new std::string(*infix), false, NULL, 0.0, err);
        }
    }

    /* Prepare prefix from stack form and execution stack */
    while (!prefix_stack->isEmpty()) {
        Op* op = prefix_stack->pop();
        prefix->append(*op->data);
        if (!prefix_stack->isEmpty()) {
            prefix->push_back(' ');
        }
        ex_stack->push(op);
    }

    return _calculate();
}

static void addStringValueForDouble(Op* op) {
    op->data = new std::string;
    op->data->append(std::to_string(op->double_val));
}

void InfixToPrefixCovertorAndCalculator::executeBinaryOperation(Op* bOp) {
    Op* res = new Op;
    Op* op1 = op_stack->pop();

    if (op1 == NULL) {
        throw FormatError("Left operator is missed for operand", bOp->position);
    }

    Op* op2 = op_stack->pop();
    if (op2 == NULL) {
        throw FormatError("Right or left operator is missed for operand", bOp->position);
    }

    double val = 0.0;
    switch (bOp->data->at(0)) {
        case '+':
            val = op1->double_val + op2->double_val;
            break;
        case '-':
            val = op1->double_val - op2->double_val;
            break;
        case '*':
            val = op1->double_val * op2->double_val;
            break;
        case '/':
            if (op2->double_val == 0.0) {
                throw FormatError("Right operator is NULL for operand \'/\'", bOp->position);
            }
            val = op1->double_val / op2->double_val;
            break;
        case '^':
            val = pow(op1->double_val, op2->double_val);
            break;
    }

    delete op1;
    delete op2;
    
    res->double_val = val;
    res->type = OpType::OperandDouble;
    res->position = bOp->position;
    delete bOp;
    addStringValueForDouble(res);
    op_stack->push(res);
}

void InfixToPrefixCovertorAndCalculator::executeFunction(Op* bOp) {
    Op* res = new Op;
    Op* op = op_stack->pop();
    if (op == NULL) {
        throw FormatError("Operator is missed for function", bOp->position);
    }

    double val = 0.0;
    if (bOp->data->compare("cos") == 0) {
        val = cos(op->double_val);
    } else if (bOp->data->compare("sin") == 0) {
        val = sin(op->double_val);
    } else if (bOp->data->compare("tg") == 0) {
        val = tan(op->double_val);
    } else if (bOp->data->compare("ctg") == 0) {
        double tg = tan(op->double_val);
        if (tg == 0.0) {
            throw FormatError("Invalid operand for \'ctg\' function", bOp->position);
        } 
        val = 1.0 / tg;
    } else if (bOp->data->compare("ln") == 0) {
        if (op->double_val > 0.0) {
            val = log(op->double_val);
        }
        else {
            throw FormatError("Not positive operand for \'ln\' function", bOp->position);
        }
    } else if (bOp->data->compare("log") == 0) {
        if (op->double_val > 0.0) {
            val = log10(op->double_val);
        }
        else {
            throw FormatError("Not positive operand for \'log\' function", bOp->position);
        }
        
    } else if (bOp->data->compare("sqrt") == 0) {
        if (op->double_val < 0.0) {
            throw FormatError("Negative operand for \'sqrt\' function", bOp->position);
        }
        val = sqrt(op->double_val);
    } else {
        val = abs(op->double_val);
    }

    delete op;
    res->double_val = val;
    res->type = OpType::OperandDouble;
    res->position = bOp->position;
    delete bOp;
    addStringValueForDouble(res);
    op_stack->push(res);
}

ConversionAndCalculationResult* InfixToPrefixCovertorAndCalculator::_calculate() {
    while (!ex_stack->isEmpty()) {
        Op* op = ex_stack->pop();
        if (op->type == OpType::OperandDouble) {
            // Add operand to stack
            setDoubleValue(op);
            op_stack->push(op);
        }
        else if (op->type == OpType::Constant) {
            // Add constant as operand to stack
            Op* operand = getDoubleTypeOfConstant(op);
            setDoubleValue(operand);
            op_stack->push(operand);
            delete op;
        } else if (op->type == OpType::Function) {
            executeFunction(op);
        }
        else if (op->type == OpType::BinaryOperator) {
            executeBinaryOperation(op);
        }
        else {
            std::string* err = new std::string("Runtime error: Calculation: Execution statck has unexpected elements. Position: ");
            err->append(std::to_string(op->position));
            err->append(", Type: ");
            err->append(std::to_string(op->type));
            err->append(", Data: ");
            err->append(*(op->data));
            return new ConversionAndCalculationResult(new std::string(*infix), false, NULL, 0.0, err);
        }
    }

    Op* last = op_stack->pop();
    if (last == NULL) {
        throw FormatError("Calculation: Invalid expression, result is not defined", 0);
    }

    if (!op_stack->isEmpty()) {
        throw FormatError("Calculation: Operands stack is not empty", 0);
    }

    double rdouble = floor(last->double_val * 1000) / 1000;
    return new ConversionAndCalculationResult(new std::string(*infix), true, new std::string(*prefix), rdouble, NULL);;
}

void InfixToPrefixCovertorAndCalculator::clean() {
    if (infix != NULL) {
        delete infix;
        infix = NULL;
    }

    if (prefix != NULL) {
        delete prefix;
        prefix = NULL;
    }

    if (prefix_stack != NULL) {
        delete prefix_stack;
        prefix_stack = NULL;
    }
    
    if (op_stack != NULL) {
        delete op_stack;
        op_stack = NULL;
    }

    if (op_stack != NULL) {
        delete op_stack;
        op_stack = NULL;
    }
}
