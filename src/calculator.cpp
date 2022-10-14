#include "../include/calculator.h"
#include <math.h>
#include <queue>
#include <stdexcept>

double Calculator::calculate(string expression, bool addToHistory) {
  list<string> expressionList = StringParser::parseExpression(expression);

  for (list<string>::iterator it = ++expressionList.begin(); it != expressionList.end(); it++) {
    if (StringParser::isOperator(*it)) {
      bool isMul = StringParser::isOperatorMultiply(*it);
      bool isDiv = StringParser::isOperatorDivide(*it);

      if (isMul || isDiv) {
        double lhs = stod(processOperand(*prev(it)));
        double rhs = stod(processOperand(*next(it)));
        double result;
        if (isMul) {
          result = lhs * rhs;
        }
        else {
          result = lhs / rhs;
        }

        expressionList.erase(next(it));
        expressionList.erase(prev(it));
        *it = to_string(result);
      }
      else {
        it++; // we need to advance twice (from this and the for iterator)
      }
    }
    else {
      throw runtime_error("Expected operator in expressionList");
    }
  }

  for (list<string>::iterator it = ++expressionList.begin(); it != expressionList.end(); it++) {
    bool isAdd = StringParser::isOperatorAdd(*it);
    bool isSub = StringParser::isOperatorSubtract(*it);
    if (!isAdd && !isSub) {
      throw runtime_error("Expected operator in expressionList");
    }
    else {
      double lhs = stod(processOperand(*prev(it)));
      double rhs = stod(processOperand(*next(it)));
      double result;
      if (isAdd) {
        result = lhs + rhs;
      }
      else {
        result = lhs - rhs;
      }

      expressionList.erase(next(it));
      expressionList.erase(prev(it));
      *it = to_string(result);
    }
  }

  if (expressionList.size() != 1) throw runtime_error("Expected expressionList of size exactly 1");
  expressionList.front() = processOperand(expressionList.front());
  double result = stod(expressionList.front());
  if (addToHistory) addHistory(expression, result);
  return result;
}

list<string> Calculator::getHistory() {
  // for return list<string>();
  return history;
}

void Calculator::deleteAllHistory() {
  // clear all history
  history.clear();
}

void Calculator::addHistory(string expression, double result) {
  history.push_back(expression + "=" + to_string(result));
}

string Calculator::processOperand(string operand) {
  if (operand.substr(0, 3) == "sin") {
    operand =
        to_string(sin(calculate(operand.substr(4, operand.size() - 5), false)));
  } else if (operand.substr(0, 3) == "cos") {
    operand =
        to_string(cos(calculate(operand.substr(4, operand.size() - 5), false)));
  } else if (operand.substr(0, 3) == "tan") {
    operand =
        to_string(tan(calculate(operand.substr(4, operand.size() - 5), false)));
  } else if (operand.substr(0, 3) == "log") {
    operand = to_string(
        log10(calculate(operand.substr(4, operand.size() - 5), false)));
  } else if (operand.substr(0, 2) == "ln") {
    operand =
        to_string(log(calculate(operand.substr(3, operand.size() - 4), false)));
  } else if (operand.substr(0, 4) == "sqrt") {
    operand = to_string(
        sqrt(calculate(operand.substr(5, operand.size() - 6), false)));
  } else if (operand.substr(0, 3) == "exp") {
    int idx = StringParser::findPositionOfCurrentExponentComma(operand);
    double base = calculate(operand.substr(4, idx - 4), false);
    double power =
        calculate(operand.substr(idx + 1, operand.size() - idx - 2), false);
    operand = to_string(pow(base, power));
  } else if (operand.front() == '(' && operand.back() == ')') {
    operand =
        to_string(calculate(operand.substr(1, operand.size() - 2), false));
  }
  return operand;
}