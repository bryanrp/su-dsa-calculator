#include "../include/string_parser.h"

list<string> StringParser::parseExpression(string expression) {
  // Widitra
  expression = changeToLowercase(removeAllSpaceFromExpression(expression));

    list<string> expressionList;
    string operand;

    int leftBracket = 0;
    bool isNowNegative = false;

    for (int index = 0; index < expression.size(); index++) {
        string current(1, expression[index]); // get the index-th character as a string
        if (current == "(") {
            leftBracket++;
        }
        if (current == ")") {
            leftBracket--;
        }
        // if (current character is "-") and (operand is still empty) and ((this is the first operand) or (the previous expression was an operator))
        if (isOperatorSubtract(current) && operand.empty() && (expressionList.empty() || isOperator(expressionList.back()))) {
            isNowNegative = true;
        }

        if (!isOperator(current) || leftBracket != 0 || isNowNegative) { // if (current character is not an operator) or (inside a bracket) or (now is negative)
            operand += current; // add current character to operand
        }
        else { // if the current character is an operator
            if (isNowNegative) {
                operand = "(0" + operand + ")"; // operand was in form of "-x". after adding "0", it becomes "(0-x)"
                isNowNegative = false;
            }
            expressionList.push_back(operand); // push the operand into the list
            operand.clear(); // clear the operand
            expressionList.push_back(current); // push the operator into the list
        }
    }
    if (isNowNegative) {
        operand = "(0" + operand + ")";
        isNowNegative = false;
    }
    expressionList.push_back(operand);

    return expressionList;

}

int StringParser::findPositionOfCurrentExponentComma(string exponentFunction) {
  // Angel
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