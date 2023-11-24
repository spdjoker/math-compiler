# Design

Features and functionality of the math compiler.

## Syntax

Reserved words: sqrt, abs, ans

Operators: +, -, \*, /, %, =, ;

Identifiers: any regex word that starts with a ASCII letter

Syntax: C-Style

## Features

Compiler converts valid file of equations and functions into a valid answer.

Example:

```math
a = 1+2;
b = -3*4;

c = 2^(sqrt(a) + abs(b));

ans = c;
```

## Math specific considerations

Operator Precedence: Parenthesis, Exponents, Multiplication/Division, Addition/Subtraction (PEMDAS)
