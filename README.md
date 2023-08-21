# Learning C
## from _The ANSI C Programming Language_ by _Kernighan_ and _Ritchie_

This is a personal study note for learning/recapping the C language.

1. A Tutorial Introduction
    * #include /<stdio.h/>
    * main()
    * printf
    * functions
        * statements
        * arguments
    * variables
    * character string (== string constant) _double quote_
        * "hello, world\n"
    * newline character
    * escape sequence
        * \n, \t, \b, \\", \\\\
    * comment
        * /\* and \*/
    * declaration
    * int, float, char, short, long, double
        * arrays, structures, unions
        * pointers
    * while
    * integer dicision truncates in C
    * %d, %3d, %6.1f
    * scanf
    * %o, %x, %c, %s, %%
    * for
    * symbolic constant
        * #define
    * text stream
    * c = getchar();
    * puchar(c);
    * EOF
    * ==, !=, >=, <=
    * ++, --
    * null statement
    * character constant (== small integer)  _single quote_
        * '\n' == 10 != "\n"
        * to see if character c is a digit, test
            * c >= '0' && c <= '9'
        * if c is a digit character, its numeric value is c - '0'
    * &&, ||
    * if else
    * array
    * switch
    * argument - call by value (vs call by reference)
        * arrays as arguments are called by reference
    * character array
    * void
    * '\0' the _null character_
    * automatic variables vs static
    * external variables
        * _defined_ (#define) once and onl once outside of any function
        * _declared_ (extern) in each function or another source file that wants to access it
        * A _header_ (#include) is a collection of extern declarations of variables and functions in a separate file.

2. Types, Operators and Expressions
    1. Variable Names
        * lower case for variable names
            * short names for local variables
            * longer names for external variables
        * all upper case for symbolic constants
    2. Data Types and Sizes
        * char (1 byte == 8 bits)
        * int (typically reflecting the natural size of integers on the host machine, like 16 or 32 bits depending on the machine)
        * float (single-precision)
        * double (double-precision)
        * int
            * short int (16 bits)
            * long int (at least 32 bits)
        * unsigned numbers obey the laws of arithmetic modulo _2^n_, where _n_ is the number of bits in the type.
        * float, double, long double
        * \<limits.h\>
        * \<float.h\>
