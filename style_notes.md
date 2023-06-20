# Coding Style

**TL;DR**: _write your code for other people_.

The objective of this guide is to build upon common coding standards to develop the **Sandbox Engine** framework so that everyone can write C++ code which is easy to read, maintain and enhance.  
Consistent style/code is easier to understand and allows the reader, programmer and contributor to concentrate on the algorithms rather than the code itself.

Refer to [1] for a complete style guide.
Some exceptions are listed below.

## C++ Standards
Currently, all code must comply with C++20.  
The C++ version targeted by this guide will advance over time.

## Header Files
In general, all `.cpp` files should have an associated `.hpp` file.  
Exceptions are allowed for unit tests and small `.cpp` files containing just a `main()` function.

### Include Guards
Use `#pragma once` instead of `#define` guards to prevent multiple inclusion.

## Brackets
Curly braces should be on their own line.  
It's easier to read and spot the scope of the variables.

```cpp
// BAD
if (...) {
    ...
}

// GOOD
if (...)
{
    ...
}
```

## Spaces vs Tabs
Use only spaces and indent 4 spaces at a time.  
Do not use tabs in the code.

## Naming
Class names use *PascalCase* and its members must start with `_`.

Variable names should use the *underscore_style*.

Function names should use *camelCase*.

Macros must use *UPPERCASE_UNDERSCORE_STYLE*

## Reference
[1] [https://google.github.io/styleguide/cppguide.html](https://google.github.io/styleguide/cppguide.html)