// This program was made by Bannikov Nikita, group 9309 
#include "pch.h"
#include "CppUnitTest.h"
#include <stdexcept>
#include "../AlgorithmKursovayaVar2/Header.h"
#include "../AlgorithmKursovayaVar2/Implementation.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace KursovayaVar2
{
    TEST_CLASS(CalculatorSuccesfulCases)
    {
    public:
        CalculatorSuccesfulCases() {
            Logger::WriteMessage(">> CalculatorSuccesfulCases, ");
            convertor = new InfixToPrefixCovertorAndCalculator;
        }

        ~CalculatorSuccesfulCases() {
            Logger::WriteMessage(" >> ~CalculatorSuccesfulCases");
            delete convertor;
        }

        TEST_METHOD(addition) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("1 + 1"));
            Assert::AreEqual(true, result->success);
            Assert::AreEqual("+ 1 1", result->prefix->c_str());
            Assert::AreEqual(2.0, result->result);
            delete result;
        }

        TEST_METHOD(subtraction) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("11 - 10"));
            Assert::AreEqual(true, result->success);
            Assert::AreEqual("- 11 10", result->prefix->c_str());
            Assert::AreEqual(1.0, result->result);
            delete result;
        }

        TEST_METHOD(multiplication) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("3 * 8"));
            Assert::AreEqual(true, result->success);
            Assert::AreEqual("* 3 8", result->prefix->c_str());
            Assert::AreEqual(24.0, result->result);
            delete result;
        }

        TEST_METHOD(division) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("21 / 7"));
            Assert::AreEqual(true, result->success);
            Assert::AreEqual("/ 21 7", result->prefix->c_str());
            Assert::AreEqual(3.0, result->result);
            delete result;
        }

        TEST_METHOD(pow) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("2 ^ 3"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "^ 2 3");
            Assert::AreEqual(8.0, result->result);
            delete result;
        }

        TEST_METHOD(unar) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("-2 * (-1 + 1) + -3"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ * -2 + -1 1 -3");
            Assert::AreEqual(-3.0, result->result);
            delete result;
        }

        TEST_METHOD(sqrt) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("sqrt(9)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "sqrt 9");
            Assert::AreEqual(3.0, result->result);
            delete result;
        }

        TEST_METHOD(abs) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("abs(-9.2)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "abs -9.2");
            Assert::AreEqual(9.2, result->result);
            delete result;
        }

        TEST_METHOD(log) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("log(100)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "log 100");
            Assert::AreEqual(2.0, result->result);
            delete result;
        }

        TEST_METHOD(ln) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("ln(2.7183)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "ln 2.7183");
            Assert::AreEqual(1.0, result->result);
            delete result;
        }

        TEST_METHOD(ln_e) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("ln(e)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "ln e");
            Assert::AreEqual(1.0, result->result);
            delete result;
        }

        TEST_METHOD(constant_e) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("e - 2.7183"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "- e 2.7183");
            Assert::AreEqual(0.0, result->result);
            delete result;
        }

        TEST_METHOD(constant_pi) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("pi / -3.14159"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "/ pi -3.14159");
            Assert::AreEqual(-1.0, result->result);
            delete result;
        }

        TEST_METHOD(cos) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("cos(pi * 60.0 / 180.0)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "cos / * pi 60.0 180.0");
            Assert::AreEqual(0.5, result->result);
            delete result;
        }

        TEST_METHOD(tg) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("tg(45.02 * pi / 180.0)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "tg / * 45.02 pi 180.0");
            Assert::AreEqual(1.0, result->result);
            delete result;
        }

        TEST_METHOD(sin) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("sin(30.01 * pi / 180.0)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "sin / * 30.01 pi 180.0");
            Assert::AreEqual(0.5, result->result);
            delete result;
        }
        
        TEST_METHOD(ctg) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("ctg(45. * pi / 180.0)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "ctg / * 45. pi 180.0");
            Assert::AreEqual(1.0, result->result);
            delete result;
        }
        
    private:
        InfixToPrefixCovertorAndCalculator* convertor;
    };

    TEST_CLASS(CalculatorSuccesfulConvertion)
    {
    public:
        CalculatorSuccesfulConvertion() {
            Logger::WriteMessage(">> CalculatorSuccesfulConvertion, ");
            convertor = new InfixToPrefixCovertorAndCalculator;
        }

        ~CalculatorSuccesfulConvertion() {
            Logger::WriteMessage(" >> ~CalculatorSuccesfulConvertion");
            delete convertor;
        }

        TEST_METHOD(simple_sum) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("1 + 3"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ 1 3");
            delete result;
        }

        TEST_METHOD(simple_plus_minus) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("1.2 - 3.4 + 11"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ - 1.2 3.4 11");
            delete result;
        }

        TEST_METHOD(simple_opertors_priority_1) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("5 + 4 * 11"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ 5 * 4 11");
            delete result;
        }

        TEST_METHOD(simple_opertors_priority_2) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("1.2*5.0 + 4.01 * 11 + 1.11"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ + * 1.2 5.0 * 4.01 11 1.11");
            delete result;
        }

        TEST_METHOD(simple_opertors_priority_3) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("1 + 16 * 10 / 2.0 + 11"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ + 1 / * 16 10 2.0 11");
            delete result;
        }

        TEST_METHOD(simple_brackets) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("(1 + 1)*5"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "* + 1 1 5");
            delete result;
        }

        TEST_METHOD(brackets_priority_1) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("(1 + 1) * 5 + 7 * (21 / 7)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ * + 1 1 5 * 7 / 21 7");
            delete result;
        }
        
        TEST_METHOD(brackets_priority_2) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("11 + (2^2 + 2) / (1^3 + 0) * 11"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ 11 * / + ^ 2 2 2 + ^ 1 3 0 11");
            delete result;
        }

        TEST_METHOD(constant_pi) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("pi * 11"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "* pi 11");
            delete result;
        }

        TEST_METHOD(constant_e) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("12 * e"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "* 12 e");
            delete result;
        }

        TEST_METHOD(constant_brackets_priority) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("(e*1.6)/(pi*1.1)"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "/ * e 1.6 * pi 1.1");
            delete result;
        }

        TEST_METHOD(unary_minus_1) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("-1 + 1"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ -1 1");
            delete result;
        }

        TEST_METHOD(unary_minus_2) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("-1 + -1"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ -1 -1");
            delete result;
        }

        TEST_METHOD(unary_minus_3) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("abs( -1) + 1"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ abs -1 1");
            delete result;
        }
        
        TEST_METHOD(unary_minus_4) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("ln(1.23) + -2.1"));
            Assert::AreEqual(result->success, true);
            Assert::AreEqual(result->prefix->c_str(), "+ ln 1.23 -2.1");
            delete result;
        }

    private:
        InfixToPrefixCovertorAndCalculator* convertor;
    };

    TEST_CLASS(CalculatorFailed)
    {
    public:
        CalculatorFailed() {
            Logger::WriteMessage(">> CalculatorFailed, ");
            convertor = new InfixToPrefixCovertorAndCalculator;
        }

        ~CalculatorFailed() {
            Logger::WriteMessage(" >> ~CalculatorFailed");
            delete convertor;
        }

        TEST_METHOD(invalid_operand_at_0) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("a12.4"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(), "Invalid operand (positon 0)");
            delete result;
        }

        TEST_METHOD(invalid_function_name) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("(1 + 234.0) / sqrtv(11)"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(), "Invalid operand (positon 14)");
            delete result;
        }

        TEST_METHOD(no_open_bracket) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("1 + 1)"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(), "Open bracket not found (positon 5)");
            delete result;
        }

        TEST_METHOD(no_close_bracket) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("(1 + 1"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(), "Close bracket not found (positon 0)");
            delete result;
        }

        TEST_METHOD(no_close_bracket_for_function) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("1 + (1 + 2) * log(11"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(), "Close bracket not found (positon 17)");
            delete result;
        }

        TEST_METHOD(missed_right_operator_for_pow) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("2^"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(), 
                "Right or left operator is missed for operand (positon 1)");
            delete result;
        }

        TEST_METHOD(missed_left_operator_for_pow) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("^"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(),
                "Left operator is missed for operand (positon 0)");
            delete result;
        }

        TEST_METHOD(zero_division) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("5 / ( 1 - 1)"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(),
                "Right operator is NULL for operand '/' (positon 2)");
            delete result;
        }

        TEST_METHOD(negative_operand_in_sqrt) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("sqrt(-9)"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(),
                "Negative operand for 'sqrt' function (positon 0)");
            delete result;
        }

        TEST_METHOD(negative_operand_in_log) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("log(-9)"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(),
                "Not positive operand for 'log' function (positon 0)");
            delete result;
        }

        TEST_METHOD(invalid_operand_in_ctg) {
            ConversionAndCalculationResult* result;
            result = convertor->calculate(new std::string("ctg(0)"));
            Assert::AreEqual(result->success, false);
            Assert::AreEqual(result->error->c_str(),
                "Invalid operand for 'ctg' function (positon 0)");
            delete result;
        }
    private:
        InfixToPrefixCovertorAndCalculator* convertor;
    };

    

    TEST_CLASS(ConversionAndCalculationResultClass)
    {
    public:
        TEST_METHOD(constructor_success) {
            ConversionAndCalculationResult* result = 
                new ConversionAndCalculationResult(
                    new std::string("A + B"), 
                    true, 
                    new std::string("+ A B"), 
                    1.1, 
                    NULL);

            Assert::AreEqual(result->infix->c_str(), "A + B");
            Assert::AreEqual(result->prefix->c_str(), "+ A B");
            Assert::AreEqual(result->result, 1.1);
            Assert::IsNull(result->error);
            Assert::AreEqual(result->success, true);

            delete result;
        }

        TEST_METHOD(constructor_fail) {
            ConversionAndCalculationResult* result  = 
                new ConversionAndCalculationResult(
                    new std::string("A + B"),
                    false, 
                    NULL, 
                    0.0,
                    new std::string("Invalid"));
            
            Assert::AreEqual(result->infix->c_str(), "A + B");
            Assert::AreEqual(result->error->c_str(), "Invalid");
            Assert::IsNull(result->prefix);
            Assert::AreEqual(result->result, 0.0);
            Assert::AreEqual(result->success, false);

            delete result;
        }
    };
    
    TEST_CLASS(OpStackClass)
    {
    public:
        OpStackClass() {
            Logger::WriteMessage(">> OpStack, ");
            stack = new OpStack;
        }

        ~OpStackClass() {
            Logger::WriteMessage(" >> ~OpStack");
            delete stack;
        }

        TEST_METHOD(is_empty) {
            Assert::AreEqual(stack->isEmpty(), true);
            stack->push(new std::string("A"), OpType::Function, 0);
            Assert::AreEqual(stack->isEmpty(), false);
        }

        TEST_METHOD(length) {
            Assert::AreEqual(stack->size(), 0);
            stack->push(new std::string("A"), OpType::OperandDouble, 0);
            Assert::AreEqual(stack->size(), 1);
            stack->push(new std::string("B"), OpType::BinaryOperator, 0);
            Assert::AreEqual(stack->size(), 2);

            Op* op = stack->pop();
            delete op;
            Assert::AreEqual(stack->size(), 1);
            op = stack->pop();
            delete op;
            Assert::AreEqual(stack->size(), 0);
        }

        TEST_METHOD(adding) {
            Assert::AreEqual(stack->isEmpty(), true);
            stack->push(new std::string("A"), OpType::Constant, 0);
            Assert::AreEqual(stack->isEmpty(), false);
            stack->peek();
            Op* op = stack->pop();
            delete op;

            Assert::AreEqual(stack->isEmpty(), true);

            stack->push(new std::string("A"), OpType::Constant, 0);
            stack->push(new std::string("B"), OpType::Constant, 0);
            stack->push(new std::string("C"), OpType::Constant, 0);
            Assert::AreEqual(stack->size(), 3);
        }

        TEST_METHOD(peek_pop) {
            stack->push(new std::string("A"), OpType::Function, 23);
            stack->push(new Op(new std::string("B"), OpType::Constant, 0));
            stack->push('C', OpType::BinaryOperator, 11);
            Assert::AreEqual(stack->size(), 3);

            Op* op;
            op = stack->peek();
            Assert::AreEqual(op->data->c_str(), "C");
            Assert::AreEqual(op->position, 11);
            Assert::AreEqual((int)op->type, (int)OpType::BinaryOperator);
            op = stack->pop();
            delete op;

            op = stack->peek();
            Assert::AreEqual(op->data->c_str(), "B");
            Assert::AreEqual(op->position, 0);
            Assert::AreEqual((int)op->type, (int)OpType::Constant);
            op = stack->pop();
            delete op;

            op = stack->peek();
            Assert::AreEqual(op->data->c_str(), "A");
            Assert::AreEqual((int)op->type, (int)OpType::Function);
            Assert::AreEqual(op->position, 23);
            op = stack->pop();
            delete op;

            op = stack->peek();
            Assert::IsNull(op);

            op = stack->pop();
            Assert::IsNull(op);

            Assert::AreEqual(stack->size(), 0);
            Assert::AreEqual(stack->isEmpty(), true);
        }

    private:
        OpStack* stack;
    };
}
