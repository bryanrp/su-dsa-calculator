#pragma once
#include "string_parser.h"
#include <list>
#include <string>
using namespace std;

class Calculator {
public:
  double calculate(string expression, bool addToHistory);
  list<string> getHistory();
  void deleteAllHistory();

private:
  list<string> history;
  void addHistory(string expression, double result);
  string processOperand(string operand);
};