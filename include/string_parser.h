#pragma once
#include <list>
#include <string>
using namespace std;

class StringParser {
public:
    static list<string> parseExpression(string expression);
    static int findPositionOfCurrentExponentComma(string exponentFunction);
    static bool isOperator(string str);
    static bool isOperatorAdd(string str);
    static bool isOperatorSubtract(string str);
    static bool isOperatorMultiply(string str);
    static bool isOperatorDivide(string str);
private:
    StringParser() {} // to avoid any object instantiation
    static string removeAllSpaceFromExpression(const string &expression);
    static string changeToLowercase(const string &expression);
};