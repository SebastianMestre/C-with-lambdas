# C with lambdas

## About

This program implements a preprocessing step that adds anonymous functions to the C language. To keep things simple -since this was made in about an hour- it does not support nesting of anonymous functions, closures, type checking, or storage in local variables (though this last one does work, if you type the function pointer syntax).

The way it achieves this is by scanning your code for anonymous function expressions, then promotes them to file scope with a (hopefully) unique name, by generating some function definitions.

## Usage

You must provide a single point in your file where the generated definitions will be inserted. To do this, you must insert the following string into your file:

```C
/*__LAMBDA__*/
```

### Syntax

Anonymous function syntax is pretty much the same as PHP, with extra parentheses that wrap the whole thing. Anonymous functions are of the form:

```
(fn (<argument-list>) : <return-type> => <body>)
```

CWL will recognize any string that does not contain the `(` character as a valid return type.

Any string that starts with `(` and has balanced brackets will be considered a valid argument list.

Any string up to the bracket that matches the one at the start of the anonymous function expression will be considered a valid body.

Extra whitespace between components of an anonymous function expression is allowed.

Here is an example:

```C
(fn (int x, int y) : int =>  x + y)
```

Parentheses are mandatory because it makes parsing easier.

#### Caveats:

The parsing is very rudimentary and not very thought-through so it's probably fragile and will unexpectedly fail on weird input.

There are no error messages in case you make a mistake, because good errors are hard.

## Build

compile using C++17

```shell
g++ -std=c++17 src/main.cpp -o cwl
```
