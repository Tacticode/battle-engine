# Coding Style

This coding style document aim to offer a basis for the consistency of the project. We are not particularly looking for performances, but more for a way to write a readable code. Therefore most of the keywords such as `inline` or `constexpr` are eluded since there are very few reason for us to use them, at least intensively.

If anything is not documented or seems obscure, please open an issue on Gitlab or simply tell us on Slack. The best reference you can find is [the C++ Core Guidelines](http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines).

## Header Files

Every *.cpp* has an equivalent *.hpp* header file.
Only exception made of the *.cpp* containing the `main()` and the unitary tests.

### Guard

All header files should start with `#pragma once`.

### Forward Declarations

Use forward declarations instead of `#include` in your headers as much as possible. This will save us some compile time.

## Scoping

### Namespace

A namespace is made of lower case characters.  
To each namespace correspond a directory in which all the files from this namespace are included.

### Pointers

`new` and `delete` are forbidden keywords. A pointer can only be initialized with `make_unique` or, **occasionally**, `make_shared`.  
Use references as much as possible.

### Local Variables

Place a function's variables in the narrowest scope possible, and initialize variables in the declaration.

Prefer initializing using brace initialization.

### Auto

Use `auto` with parsimony. `auto` should be used very rarely. An iterator can be avoided with the `for (type e : dataStructure)` of C++11.  
`auto` makes the code hard to read without an IDE.

## Classes

Always follow the [Rule of Five](http://en.cppreference.com/w/cpp/language/rule_of_three).

### Constructor

Use `explicit` for all your constructors unless you specifically want to allow an implicit initialization of your class (bracket initialization).

### Interfaces

Use interfaces as much as you can and always for multiple inheritance.

### Private & Const

Never make a class veriable public, use a struct if you just want to create a package of variables.  
Use `const` everywhere you should (getter, pointer variables, references...).

## Functions

 * Write short functions
 
 * Limit a line to 120 column
  
### Casting
  
Never use C casts. Use C++ casts, including the [pointer casts](http://en.cppreference.com/w/cpp/memory/shared_ptr/pointer_cast).
  
### Nullptr
  
Use the C++11 `nullptr` instead of 0 or NULL when evaluating a pointer value.
  
## Naming
  
We use camelCase for everything except:
  
 * Types in UpperCamelCase
 * MACRO in UPPER_SNAKE_CASE
	
## Comments
	
Use comments to explain the intention behind a function/class when you fee it might be necessary for an easier comprehension.
	 
## Formating
	 
Use tabulations to indent, spaces to align. Never mix tabulation and spaces.
	 
## CMake
	 
Each namespace directory contains a CMakeLists.txt listing its files.