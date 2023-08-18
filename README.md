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
        * \n, \t, \b, \", \\
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


