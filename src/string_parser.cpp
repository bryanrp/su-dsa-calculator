#include "../include/string_parser.h"

list<string> StringParser::parseExpression(string expression) {
  // Widitra
  return list<string>();
}

int StringParser::findPositionOfCurrentExponentComma(string exponentFunction) {
  // Sidan
  return 0;
}

bool StringParser::isOperator(string str) {
  if (str == "+" || str == "-" || str == "*" || str == "/")
    return true;
  return false;
}

bool StringParser::isOperatorAdd(string str) {
  if (str == "+")
    return true;
  return false;
}

bool StringParser::isOperatorSubtract(string str) {
  if (str == "-")
    return true;
  return false;
}

bool StringParser::isOperatorMultiply(string str) {
  if (str == "*")
    return true;
  return false;
}

bool StringParser::isOperatorDivide(string str) {
  if (str == "/")
    return true;
  return false;
}

string StringParser::removeAllSpaceFromExpression(const string &expression)
{
  string notBlank;
  for (int i = 0; i < expression.size(); i++) 
  {
    if (expression[i] == ' ')
    {
      
    }
      else 
      {
        notBlank = notBlank + (char)expression[i];  
      }
  }
  
  return notBlank;
}

string StringParser::changeToLowercase(const string &expression) 
{
  string lowresult;
  for (int i = 0; i < expression.size(); i++) 
  {
    lowresult = lowresult + (char)tolower(expression[i]);
  }
  return lowresult;
}