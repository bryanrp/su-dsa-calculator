# documentation

This is only an overview. For in-depth algorithm explanation, check for comments in each file.

## Directory structure

```bash
su-dsa-calculator
│   .gitignore
│   documentation.md
│   main.cpp
│   README.md
├───include
│       calculator.h
│       string_parser.h
└───src
        calculator.cpp
        string_parser.cpp
```

## Contents
- [main.cpp](#main)
- [string_parser.h and string_parser.cpp](#string_parser)
    - [parseExpression](#parseExpression)
    - [findPositionOfCurrentExponentComma](#findPosOfExpComma)
    - [isOperator](#isOperator)
    - [removeAllSpaceFromExpression](#removeSpace)
    - [changeToLowercase](#changeToLower)
- [calculator.h and calculator.cpp](#calculator)
    - [calculate](#calculate)
    - [processOperand](#processOperand)
    - [getHistory](#getHistory)
    - [deleteAllHistory](#deleteAllHistory)
    - [addHistory](#addHistory)

## <a id="main"></a>main.cpp

This is where the `int main()` is located.

To use the calculator, instantiate a new `Calculator` object:
```c++
Calculator calculator;
```

Call `calculator.calculate(expression, addToHistory)` to get the result of an `expression`. Pass `addToHistory` as `true` if you want to record this expression to the history. Example:

1. `double result = calculator.calculate("1 + 1", true)` will set the value of `result` to be `2`.
2. `double answer = calculator.calculate("sqrt(exp(log(100), 2)) - (-2) * (-2)", false)` will set the value of `answer` to be `-2`. Notice that the second argument `addToHistory` is `false`, which means that this calculation will not be recorded into the history.

Call `calculator.getHistory()` to get all history as a list of strings (`list<string>`). `list` is just like an array, with an exception that you can not access the element with index. Example:

```c++
list<string> history = calculator.getHistory();
for (string str : history) {
    cout << str << '\n';
}
```

```c++
// this code won't work
list<string> history = calculator.getHistory();
int size = history.size();
for (int i = 0; i < size; i++) {
    cout << history[i] << '\n'; // no such thing as history[i], since it is a `list`
}
```

Call `calculator.deleteAllHistory()` to delete all history.

## <a id="string_parser"></a>string_parser.h and string_parser.cpp

### <a id="parseExpression"></a>`list<string> parseExpression(string expression)`

Essentially, all expressions contain either an operand or operator. 
Separate the expression into multiple `string`s, each representing either an operand or operator. Example:

1. `expression = "1 + 2 * (3 + 4)"`

    The function is expected to return `["1", "+", "2", "*", "(3 + 4)"]`. Notice that these `string`s represent `[operand, operator, operand, operator, and operand]` respectively. What about `"(3 + 4)"`? We can call this function again `parseExpression("3 + 4")`, and it is expected to return `["3", "+", "4"]`.

2. `expression = "sin(3.14 / 2) / exp(exp(2, 2), 2)"`

    The function is expected to return `["sin(3.14 / 2)", "/", "exp(exp(2, 2), 2)"]`.

Note that before we process the `expression`, we should write the following line to make the expression simpler (no excessive space character or bad function names like `sIN` or `SQrt`).
```c++
expression = changeToLowercase(removeAllSpaceFromExpression(expression));
```

### <a id="findPosOfExpComma"></a>`int findPositionOfCurrentExponentComma(string exponentFunction)`

Notice the `exp(exp(2, 2), 2)` expression on the second example above. There are two commas in the `string`, and we need to determine which comma is going to be used for the current `exp()` expression. Example:

1. `exponentFunction = "exp(2, 2)"`

    The function is expected to return `5`. We count the position in a `string` starting from `0`. So the zeroth char is `e`, the first char is `x`, the second char is `p`, and so on.

2. `exponentFunction = "exp(exp(2, 2), sqrt(4))"`

    The function is expected to return `13`. Do not forget to count the space characters.

### <a id="isOperator"></a>`bool isOperator(string str)`

Returns whether `str` is equal to either `"+"`, `"-"`, `"*"`, or `"/"`. The same logic applies to `isOperatorAdd`, `isOperatorSubtract`, `isOperatorMultiply`, and `isOperatorDivide`.

Why did we make these functions? Why do we need to write `if (isOperatorAdd(str))` instead of the simpler `if (str == "+")`? Well let's say that later in the future, we want to handle `':'` character as an alternative for `'/'`. Now we only need to change the code inside `isOperatorDivide`, no need to change all occurences of `if (str == "/")`.

### <a id="removeSpace"></a>`string removeAllSpaceFromExpression(const string &expression)`

Returns the `expression` string after all of its space characters removed. For example, if `expression = "2 +3 * sin( exp( 2 , 2 ) )"` was given, then the function is expected to return `"2+3*sin(exp(2,2))"`.

### <a id="changeToLower"></a>`string changeToLowercase(const string &expression)`

Returns the `expression` string with all uppercase changed to lowercase. For example, if `expression = "SqRT(TaN(10))"` was given, then the function is expected to return `"sqrt(tan(10))"`.

## <a id="calculator"></a>calculator.h and calculator.cpp

### <a id="calculate"></a>`double calculate(string expression, bool addToHistory)`

Returns the result of the given `expression` and add to calculator's history if `addToHistory` is `true`. Inside, it will call `StringParser::parseExpression` function to parse the expression. Example:

1. `expression = "1 + 2 * (3 + 4)"`, `addToHistory = true`

    The function is expected to return `21.00000` (the number of trailing zeroes may vary). Inside, it will call `StringParser::parseExpression` and store its returned value `["1", "+", "2", "*", "(3 + 4)"]`. For the last `string`, we can call `calculate("3 + 4", false)` to get its value. In the end, we have `["1", "+", "2", "*", "7"]`.
    
    Notice that the odd-indexed `string`s (we start counting from 0) are operators. We can process the expression from `*` and `/` then followed by `+` and `-`.
    
    - `["1", "+", "2", "*", "7"]`
    - `["1", "+", "14"]`
    - `["15"]`

    After that, since `addToHistory = true`, we add `(expression + " = " + result)` to the history. Recall that we called `calculate("3 + 4", false)`. `addToHistory = false` so that `3 + 4` is not added to history.

2. `expression = "sin(3.14 / 2) / exp(exp(2, 2), 2)"`, `addToHistory = true`

    The function is expected to return `0.06250` (the number of traling zeroes may vary). Inside, it will also call `StringParser::parseExpression` like the first example. Additionally, it will also calls:

    - `calculate("3.14 / 2", false)`, to resolve sin(**3.14 / 2**)
    - `calculate("exp(2, 2)", false)`, to resolve exp(**exp(2, 2)**, 2)
        - `calculate("2", false)`, to resolve exp(**2**, 2)
        - `calculate("2", false)`, to resolve exp(2, **2**)
    - `calculate("2", false)`, to resolve exp(exp(2, 2), **2**)

### <a id="processOperand"></a>`string processOperand(string operand)`

Different "types" of operand:

1. Basic number: `12`, `0.5`, and `-100.00`.

    For this case, the function is expected to return the `operand` as it is.

2. Function: `sin(1)`, `cos(0)`, `tan(1)`, `log(10)`, `ln(2.71)`, `sqrt(2)`, and `exp(2, 2)`.

    For this case, the function `processOperand` is expected to return the `operand` after executing the function (`sin`, `tan`, `sqrt`, etc). Example:

    1. `operand = "log(10 * 10)"`

        The function will call `calculate("10 * 10", false)` first to get the result of the inner bracket. After that, the function will calculate `log(100)` using C++ builtin function: `log10(100)`. It will return the value `2` as a string `"2"`.

    2. `operand = "exp(exp(2, 2), 2)"`

        The function will call `calculate("exp(2, 2)", false)` and `calculate("2", false)`. After receiving the result, it will calculate `exp(4, 2)` using C++ builtin function: `pow(4, 2)`. It will return the value `16` as a string `"16"`.

3. "Bracketed": `(1)`, `((-2))`, and `(1 / 2)`.

    For this case, the function is expected to return the value of `calculate(innerBracket, false)`, where `innerBracket` is the expression inside the bracket. Example:

    1. `operand = "(1 / 2)"`. It will return the value of `calculate("1 / 2", false)` as a string.
    2. `operand = "((1 / 2))"`. It will return the value of `calculate("(1 / 2)", false)` as a string.

### <a id="getHistory"></a>`list<string> getHistory()`

Returns all history. Example:
- `["1 + 2 = 3", "cos(3.14) - sqrt(1) = -2", "exp(2, 2) = 4"]`, 3 calculations
- `["1/2 + 2 = 2.5"]`, only 1 calculation
- `[]`, no history

### <a id="deleteAllHistory"></a>`void deleteAllHistory()`

Delete all history.

### <a id="addHistory"></a>`void addHistory(string expression, double result)`

This function is expected to add `expression + " = " + result` to the `history`. This function will be called by `calculate(expression, addToHistory)` if `addToHistory = true`. Example:

- `calculate("1 +2", true)` will call `addHistory("1 +2", 3)`.
- `calculate("1 +2", false)` will **not** call `addHistory()`, since `addToHistory = false`.
- `calculate("sin(3.14 / 2) / exp(exp(2, 2), 2)", true)` will call `addHistory("sin(3.14 / 2) / exp(exp(2, 2), 2)", 0.06250)`