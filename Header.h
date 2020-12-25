// This program was made by Bannikov Nikita, group 9309 
#pragma once
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

enum OpType { BinaryOperator, OperandDouble, Function, Constant, Bracket, Unknown };

class Op {
public:
    Op() {};
    Op(std::string* data_val, OpType type_val, int position_val) {
        data = data_val;
        type = type_val;
        position = position_val;
    };

    Op(char c, OpType type_val, int position_val) {
        data = data = new std::string;
        data->push_back(c);
        type = type_val;
        position = position_val;
    };

    ~Op() {
        if (data != NULL) {
            delete data;
        }
    }
    std::string* data = NULL;
    int position = 0;
    double double_val = 0.0;
    OpType type = OpType::Unknown;
    Op* next = NULL;
};

class OpStack {
private:
    Op* head;
    int length;
public:
    OpStack() {
        head = NULL;
        length = 0;
    }
    ~OpStack() {
        while (!isEmpty()) {
            Op* op = pop();
            delete op;
        }
    }
    void push(std::string*, OpType, int);
    void push(char, OpType, int);
    void push(Op*);
    Op* pop();
    Op* peek();
    void printStack();
    bool isEmpty();
    int size() { return length; };
};


class ConversionAndCalculationResult {
public:
    ConversionAndCalculationResult(std::string* infix_val, bool sucess_val, std::string* prefix_val, double result_val, std::string* error_val) {
        infix   = infix_val;
        success = sucess_val;
        prefix  = prefix_val;
        error   = error_val;
        result  = result_val;
    };

    ~ConversionAndCalculationResult() {
        if (prefix != NULL) {
            delete prefix;
            prefix = NULL;
        }

        if (infix != NULL) {
            delete infix;
            infix = NULL;
        }

        if (error != NULL) {
            delete error;
            error = NULL;
        }
    };

    bool success;
    double result;
    std::string* infix;
    std::string* prefix ;
    std::string* error;
};

/* The convertor / calculator */
class InfixToPrefixCovertorAndCalculator {
public:
    InfixToPrefixCovertorAndCalculator() {
    }

    ~InfixToPrefixCovertorAndCalculator() {
        clean();
    }

    ConversionAndCalculationResult* calculate(std::string*);
private:
    ConversionAndCalculationResult* _convert_and_calculate();
    ConversionAndCalculationResult* _calculate();
    static bool isSeparator(char);
    static bool isOperator(char);
    static int stackOperatorPriority(Op*);
    static int currentOperatorPriority(Op*);
    static bool isBracket(char);
    static OpType getOpType(std::string);
    static Op* getDoubleTypeOfConstant(Op*);
    void executeBinaryOperation(Op*);
    void executeFunction(Op*);
    void clean();

    /* Infix input string */
    std::string* infix  = NULL;
    /* Normalized prefix string */
    std::string* prefix = NULL;
    /* Stack for forming prefix at conversion */
    OpStack* prefix_stack = NULL;
    /* Opertaors/brackets stack at conversion */
    OpStack* op_stack = NULL;
    /* Prefix execution stack at calculation */
    OpStack* ex_stack = NULL;
};

/* Internal exception class */
class FormatError : public std::invalid_argument
{
public:
    FormatError(const std::string& msg, int position) :
        std::invalid_argument("")
    {
        std::stringstream ss;
        ss << msg << " (positon " << position << ")";
        static_cast<std::invalid_argument&>(*this) = std::invalid_argument(ss.str());
    }
};
