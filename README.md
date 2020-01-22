# C with lambdas

## About

This program implements a preprocessing step that adds anonymous functions to the C language. To keep things simple -this was made in about an hour- it does not support nesting of anonymous functions, closures, type checking, or storage in local varaibles (though this last one does work, if you type the function pointer syntax).

## Syntax

An anonymous function looks as follows:

```
(fn <return-type> <argument-list> => <body>)
```

CWL will recognize any string that does not contain the `(` character as a valid return type.

Any string that starts with `(` and has balanced brackets will be considered a valid argument list.

Any string up to the bracket that matches the one at the start of the anonymous function expression will be considered a valid body.

Here is an example:

```C
(fn int(int x, int y) =>  x + y)
```

The parentheses are mandatory (the reason is that it made parsing easier).

## Build

compile using C++17

```shell
g++ -std=c++17 src/main.cpp -o cwl
```
