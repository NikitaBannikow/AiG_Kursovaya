// This program was made by Bannikov Nikita, group 9309 
#include "Header.h"
#include <iostream>
#include <locale>
#include <fstream>



/* Prints calculator resut to console */
void print_calculator_result(std::string* infix, ConversionAndCalculationResult* result) {
    std::cout << "Prefix convertion/calculation result: " << infix->c_str() << endl;
    if (result->success) {
        std::cout << "  Success: " << result->prefix->c_str() << endl;
        std::cout << "  Result:  " << result->result << endl;
    }
    else {
        std::cout << "  Failed: " << result->error->c_str() << endl;
    }
}

/* Debug converter/calculator */
void debug_calculator() {
    try {
        std::string* infix = new std::string("1 + 16 * 10 / 2.0 + 11");

        ConversionAndCalculationResult* result;
        InfixToPrefixCovertorAndCalculator* convertor = new InfixToPrefixCovertorAndCalculator();

        result = convertor->calculate(infix);
        print_calculator_result(infix, result);
        delete result;
        delete convertor;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

static std::string trim(const std::string& str,
    const std::string& whitespace = " \t")
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

static vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string dirty_token = str.substr(prev, pos - prev);
        string token = trim(dirty_token);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

static double getDoubleValue(std::string double_val) {
    try {
        char* stopstring;
        double x = strtod(double_val.c_str(), &stopstring);
        if (strlen(stopstring) == 0) {
            double normalized = (x * 100.0) / 100.0;
            return normalized;
        }
    }
    catch (const std::invalid_argument& e) {
    }
    throw invalid_argument("Can not covert double");
}

const char* FILE_NAME = "input.txt";
/**
 * File format: infix;expected_prefix;expected_result
 *   where <expected_result>:
 *		'failed'     - if operation shall be failed
 *      double value - expected result of expression 
 */
void process_file() {
    std::ifstream file(FILE_NAME);
    if (file.is_open()) {
        std::string str;
        int line_num = 0;
        int passed = 0;
        int failed = 0;
        std::cout << "Running..." << endl;
        while (std::getline(file, str)) {
            line_num += 1;
            string delimiter = ";";
            vector<string> tokens = split(str, delimiter);
            
            if (tokens.size() != 3) {
                std::cout << "Error: Invalid format in line " << line_num << " of file " << FILE_NAME << endl;
            } else {
                std::string* infix           = new std::string(tokens.at(0));
                std::string expected_prefix  = tokens.at(1);
                std::string expected_result  = tokens.at(2);

                try {
                    ConversionAndCalculationResult* result;
                    InfixToPrefixCovertorAndCalculator* convertor = new InfixToPrefixCovertorAndCalculator();

                    result = convertor->calculate(infix);

                    if (expected_result.compare("failed") == 0) {
                        if (result->success) {
                            failed += 1;
                            std::cout << "Error at line " << line_num << ": Expected fail, but got success" << endl;
                        }
                        else {
                            passed += 1;
                        }
                    }
                    else {
                        if (result->success) {
                            if (expected_prefix.compare(result->prefix->c_str()) == 0) {
                                double expected_double = getDoubleValue(expected_result);
                                if (expected_double == result->result) {
                                    passed += 1;
                                }
                                else {
                                    failed += 1;
                                    std::cout << "Error at line " << line_num
                                        << ": Expected success, but result does not equal to expected one" << endl;
                                    std::cout << "   Expected: " << expected_double << endl;
                                    std::cout << "   Actual:   " << result->result << endl;
                                }
                            }
                            else {
                                failed += 1;
                                std::cout << "Error at line " << line_num
                                    << ": Expected success, but prefix in result does not equal to expected one" << endl;
                                std::cout << "   Expected: \'" << expected_prefix.c_str() << "\'" << endl;
                                std::cout << "   Actual:   \'" << result->prefix->c_str() << "\'" << endl;
                            }
                        }
                        else {
                            failed += 1;
                            std::cout << "Error at line " << line_num << ": Expected success, but got fail: " << result->error->c_str() << endl;
                        }
                    }

                    delete result;
                    delete convertor;
                }
                catch (const std::exception& e) {
                    std::cout << "Uncaught exception in line " << line_num  << ": " << e.what() << std::endl;
                }
            }
        }
        file.close();
        std::cout << "======================" << endl;
        std::cout << "Passed: " << passed << ", Failed: " << failed << endl;
        return;
    }
    std::cout << "Error: Can't open file " << FILE_NAME << endl;
}

void main() {
    //debug_calculator();
    process_file();
}
