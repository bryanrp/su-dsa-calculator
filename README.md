# su-dsa-calculator

## Manual

- The only allowed basic operators are addition (`+`), subtraction (`-`), multiplication (`*`), and division (`/`).
- Supported functions: `sin(x)`, `cos(x)`, `tan(x)`, `sqrt(x)`, `exp(x, y)`, `log(x)`, and `ln(x)`.
    - The `sin`, `cos`, and `tan` input angle is in radian.
- No limitation on the number of inputted numbers, operators, and functions.
- For negative number, try to surround it with a bracket. For example, `1 - (-1)` and `(-cos(0)) + 2`. Inputting an expression such as `1 - -1` might lead to unexpected result.
- Can show and delete the history of past calculations.
- Examples of valid expression:
    - `3 * 2 + 2 - 3 / 2`
    - `(2 + (1)) - (-3 ) *4`
    - `exp(exp(3, 2), (-2))`
    - `log(cos(0.01))*cos(0)+ln(ln(35)+80)-cos(sin(tan(7.85)))`