# Learning C
## from _The ANSI C Programming Language_ by _Brian W. Kernighan_ and _Dennis M. Ritchie_
### Solutions to exercise problems

Hi, my name is Steve, and I'd always wanted to understand how computer hardwares, memory spaces, and operating systems are controlled by **(the mighty) C**. Last year was fortunate enough for me to have some time into learning the core basics of the language, and I couldn't help grabbing the seminal book of C, _The ANSI C Programming Language_ by _K&R_. It was an exciting journey to see how I/O are handled at low level, and working on the exercise problems filled in some of the knowledge gaps I had in low-level programming.

This repo contains all the solutions I worked on the exercise problems from the book. I aimed to answer all the problems in the beginning, but had to skip a few of them unfortunately for reasonable excuses which I left in source files as comments. I didn't mean to make the repo public in the beginning, and some source & header dependancies are mixed as I moved files to their relevant directories. I mean to make them clean someday, and I believe whoever's going through the book while having my solutions as their study aid would not have serious difficulties understanding the code.

The purpose of this repo is to provide a quick glimpse of important features and usage of the C language whenever I need a reminder. I'm hoping that I could share my experience with those who're on pilgrimage to C for whatever reasons. It would be a great honor if somebody wishes to create a pull request to improve this repo.

Jan 18 2024
Sugil Steve Lee

## Chapters

## 1. [A Tutorial Introduction](Chapter_1_-_A_Tutorial_Introduction/README.md)
	- "Hello, World!\n"
	- Fahrenheit-Celsius table
	- Symbolic Constants #define
	- File copying with c = getchar(), putchar(c). copy(...)
	- Word, digit, space, character, line counter
	- Functions, getline(...)
	- Local: automatic, static
	- External - must be declared each time if defined in other (header) file
## 2. [Types, Operators and Expressions](Chapter_2_-_Types_Operators_and_Expressions/README.md)
	- Variable Names: '\_'
	- Data Types and Sizes: char, int, float, double, short, long, signed/unsigned - <limits.h>, <float.h>
	- Constants: decimal (123.4), exponent (1e-2), octal (0123), hexadecimal (0xaa, 0XFF), long (L), unsigned (U) - 0XFUL
	- Character constants 'x', escape sequence '\n', '\013', '\xb'
	- Constant expression: constant only, can be evaluated during compilation
	- String constant (string literal): \"hello, \" \"world\" - can be concatenated at compile time. strlen(...), <string.h>.
	- Enumeration constant: enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
	- Declarations: declaration, initialization, const - int strlen(const char[]);
	- Arithmetic Operators: +, -, \*, /, %
	- Relational and Logical Operators: >, >=, <, <=, ==, !=, &&, ||, !
	- Type Conversions: atoi(s), tolower(c), isdigit(c), <ctype.h>, <math.h>, rand(), srand(...), htoi(s)
	- Increment and Decrement Operators: prefix (++n, --n), postfix (n++, n--), squeeze(s1, s2), strpbrk(s1, s2)
	- Bitwise Operators: &, |, ^, <<, >>, ~, n & 0177, x | SET_ON, x & ~077, getbits(...), setbits(...), invert(...), rightrot(...)
	- Assignment Operators and Expressions: +=
	- Conditional Expressions: expr1 ? expr2 : expr3
	- Precedence and Order of Evaluation
## 3. [Control Flow](Chapter_3_-_Control_Flow/README.md)
	- Statements and Blocks
	- If-Else, Else-If, binsearch(...)
	- Switch: digit counter, escape(...)
	- Loops - While and For: atoi(...), shellsort(...), reverse(...), expand(...)
	- Loops - Do-While: the body is executed at least once, itoa(...), itob(...)
	- Break and Continue, Goto and labels
## 4. [Functions and Program Structure](Chapter_4_-_Functions_and_Program_Structure/README.md)
	- Basics of Functions: strindex(...)
	- Functions Returning Non-integers: atof(...), <stdlib.h>, calculator, atoi(...)
	- External Variables: reverse Polish calculator (push-pop, getop, getch-ungetch, buf[BUFSIZ]), ungets(...).
	- Scope Rules (definition vs. extern declarations), Header Files, Static Variables - internal static variables
	- Register Variables: faster (if applicable)
	- Block Structure, Initialization
	- Recursion: printd(...), qsort(...), swap(...), itoa(...), reverse(...)
	- The C Preprocessor: File Inclusion (#include), Macro Substitution (#define), Conditional Inclusion (#if defined(name), #endif, #ifndef)
## 5. [Pointers and Arrays](Chapter_5_-_Pointers_and_Arrays/README.md)
	- Pointers and Addresses, Function Arguments, Arrays
	- Address Arithmetic: allocbuf(...), alloc(...), afree(...)
	- Character Pointers and Functions: strcpy(...), strcmp(...), <string.h>, strcat(...), strend(...), strncpy, strncat, strncmp
	- Pointer Arrays; Pointers to Pointers: qsort lines, readlines(...), writelines(...), qsort(...), swap(...)
	- Multi-dimensional Arrays: daytab\[i]\[j], day_of_year(...), month_day(...)
	- Initialization of Pointer Arrays: month_name(...)
	- Pointers vs. Multi-dimensional Arrays: int a\[10]\[20]; vs. int \*b\[10]; - b has 10 pointers b[i] pointing to variable sizes, not like each a[i] taking up 20 sizes
	- Command-line Arguments: argc, \*argv\[] - echo, find, expr, entab, detab, tail
	- Pointers to Functions: void qsort(..., int (\*comp)(void \*, void \*)); qsort(...)(numeric ? numcmp : strcmp);
	- Complicated Declarations: int \*f(); vs. int (\*pf)();. typedef, declaration parsing (dcl, direct-dcl, token), undcl
## 6. [Structures](Chapter_6_-_Structures/README.md)
	- struct point { int x; int y; } pt1, pt2;, struct point makepoint(int, int);, pt->x
	- Arrays of Structures: struct key { char \*word; int count; } keytab\[NKEYS];, binsearch(...), sizeof, #define NKEYS (sizeof keytab / sizeof(struct key))
	- Pointers to Structures
	- Self-referential Structures: **binary tree**, treeprint, tnode.
	- Table Lookup: **hash search**, hashtab[hash_value_of_word] -> nlist -> nlist -> NULL, #define, #undef
	- Typedef
	- Unions
	- Bit-fields
## 7. [Input and Output](Chapter_7_-_Input_and_Output/README.md)
## 8. [The UNIX System Interface](Chapter_8_-_The_Unix_System_Interface/README.md)
