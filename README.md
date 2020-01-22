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

Extra whitespace between components of an anonymous function expression is allowed.

Here is an example:

```C
(fn int(int x, int y) =>  x + y)
```

Yes, the parentheses are mandatory (the reason is that it made parsing easier).

Caveats:

The parsing is very rudimentary and not very thought-through so it's probably fragile and will unexpectedly fail on weird input.

There are no error messages in case you make a mistake, because good errors are hard.

## Build

compile using C++17

```shell
g++ -std=c++17 src/main.cpp -o cwl
```
