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
    3. Constants
    	* long: 123l or 123L
    	* float: 1.23f or 1.23F
    	* long double: 1.23l or 1.23L
    	* octal: 0123
    	* hexadecimal: 0x123 or 0X123
    	* unsigned long hexadecimal: 0X\*UL
    	* character _constant_: 'x'
    	* '0' != 0 == '\0' null constant
    	* escape sequences
    		* new line: '\n'
    		* octal: '\123'
    		* hex: '\xFF'
    		* '\a' alert (bell) character
    		* '\b' backspace
    		* '\f' formfeed (?)
    		* '\r' carriage return (?)
    		* '\t' horizontal tab
    		* '\v' vertical tab
    		* '\\' backslash
    		* \? question mark
    		* \' single quote
    		* \" double quote
    	* constant _expression_
    		* #define MAXLINE 1000;
    		* evaluated at during compilation rather than run-time (no need to specify type)
    	* string _constant_ (string literal) "I am a string"
    		* concatenation: "a " "b" == "a b"
    	* enumeration _constant_
    		* enum boolean { NO, YES };
    		* enum values are 0, 1, 2, ... unless explicitly specified.
    		* enum escapes { BELL = '\a', BACKSPACE = '\b', TAB = '\t', NEWLINE = '\n', VTAB = '\v', RETURN = '\r' };
    		* enum months { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC }; /* FEB = 2, MAR =3, etc. \*/
    			* a good alternative to #define
    			* compilers need not check that what you store in such a variable is a valid value for the enumeration.
    			* a debugger may be able to print values of enumeration variables in their symbolic form.
    4. Declarations
    	* int lower, upper, step;
    	* char c, line[1000];
    	* float eps = 1.0e-5;
        * the equal sign expression serves as an initializer.
        * automatic variable = local variable
        * automatic variables are initialized each time the function or block it is in is entered.
        * const char msd[] = "warning: ";
        * int strlen(const char[]);
    5. Arithmetic Operators
        * +, -, \*, /, %
        * integer division truncates any fractional part
    6. Relational and Logical Operators
        * >, >=, <, <=
        * ==, !=
        * &&, ||
        * The unary negation operator ! convers a non-zero operand into 0, and a zero operand in 1.
            * if (!valid)
    7. Type Conversions
        * char
        * if s[] = "1234" and we want to convert it into an integer 1234, use s[i] - '0' for all i to get 1, 2, 3, 4.
        * to convert c = 'X' into 'x' _for the ASCII character set_ (only), use c - ('A' - 'a') = c + 'a' - 'A'.
        * isdigit(c)
        * For portability, specify _signed_ or _unsigned_ if non-character data is to be stored in _char_ variables.
        * cast
            * sqrt((double) n)
        * see formulae for rand in the standard libraries
	8. Increment and Decrement Operators
		* if n = 5,
			* x = n++; gives x = 5,
			* x = ++n; gives x = 6.
		* s[j++] = s[i];
		* s[j] = s[i]; j++;
		* s[i++] = t[j++];
	9. Bitwise Operators
		* & bitwise AND
		* | bitwise inclusive OR
		* ^ bitwise exclusive OR
		* << left shift
		* >> right shift
		* ~ complement
		* n = n & 0177;
    10. Assignment Operators and Expressions
        * +=, -=, \*=, /=, %=, <<=, >>=, &=, ^=, |=
        * yyval[yypv[p3+p4] + yypv[p1]] += 2
    11. Conditional Expressions
        * if (expr1) expr2; else expr3;
        * expr1 ? expr2 : expr3
        * z = (a > b) ? a : b;  /* z = max(a, b) \*/
        * for (i=0; i\<n; ++i) printf("%6d%c", a[i], (i%10==9 || i==n-1) ? '\n' : ' ');
        * printf("You have %d items%s.\n", n==1 ? "" : "s");
    12. Precedence and Order of Evaluation
        * () [] -> /
        * ! ~ ++ -- + - * sizeof
        * \* / %
        * \+ \-
        * \<\< \>\>
        * \< \<= \> \>=
        * == !=
        * &
        * ^
        * |
        * &&
        * ||
        * ?:
        * = += -= \*= /= %= &= ^= |= \<\<= \>\>=
        * ,
        * C does not specify the order in which the operands of an operator are evaluated.
            * x = f() + g();    /* wrong \*/
            * if either f or g alters a variable on which theother depends, x can depend on the order of evaluation.
        * The order in which function arguments are evaluated is not specified.
            * printf("%d %d\n", ++n, power(2, n));  /* wrong \*/
        * a[i] = i++;   /* wrong \*/
3. Control Flow
    1. Statements and Blocks
        * expression
        * statement
            * ; statement terminator
        * Braces { and } are used to group a _compound statement_, or _block_.
    2. If-Else
        * if (expression) {statement} else {statement}
    3. Else-If
        * if (expression) {statement} else if (expression) {statement} else {statement}
        * binary search
    4. Switch
        * one of a number of _constant_ integer values
        * switch (expression) {
                case const-expr: statements
                case const-expr: statements
                defult: statements
            }
    5. Loops - While and For
        * while (expression)
            statement
        * A matter of preference
        * When no initialization or increment conditions, then while is more natural
    6. Loops - Do-While
        * Tests the termination condition at the bottom
        * do
             statement
          while (expression);
        * Useful when at least one loop expression should be executed (like storing at least one data in an array)
    7. Break and Continue
        * Not neccessary
        * Useful when the loop is too complicated
    8. Goto and Labels
        * Not neccessary
        * To abandon processing in some deply nested structure
        * Break cannot easily replace Goto in the following exaple:
            for (...)
                for (...) {
                    ...
                    if (disaster)
                        goto error;
                }
            ...
            error:
                /\* clean up the mess \*/
4. Functions and Program Structure
	1. Basics of Functions
        * A program is just a set of definitions of variables and functions. Functions can occur in any order in the source file, and the source program can be split into multiple files, so long as no function is split.
        * gcc main.c getline.c strindex.c
            -> main.o getline.o strindex.o (object files, each in assembly language of the corresponding source file, will be combined with the linker once all source files caused no issues in compiling.)
	2. Functions Returning Non-integers
        * double atof(char []);
        * Such declaration is required for type clarity.
	3. External Variables
        * Functions are always external because C does not allow functions to be defined inside other functions.
	4. Scope Rules
    	* If an external variable is to be referred to before it is defined, or if it is defined in a different source file from the one where it is being used, then an *extern* declaration is ***mandatory***.
		* definition
			* double val[MAXVAL];
		* declaration
			* extern double val[];
	5. Header Files
	6. Static Variables
    	* The static declaration, applied to an external variable or function, limits the scope of that object to the rest of the source file being compiled.
    	* static char buf[BUFSIZE];
		* The static declaration can also be applied to internl variables. Internal static variables are local to a particular function just as automatic variables are, but unlike automatics, they remain in existence rather than coming and going each time the function is activated. This means that internal static variables provide private, permanent storage within a single function.
	7. Register Variables
		* Register variables are (to be) stored in machine registers.
	8. Block Structure
		* As a matter of style, it's best to avoid variable names that conceal names in an outer scope; the potential of confusion and error is too great.
	9. Initialization
    	* external and static variables are initialized to zero.
		* The initializer must be a constant expression.
		* The initialization is done once, conceptually before the program begins execution.
		* automatic and register variables have undefined (i.e., garbage) initial values.
		* The initializer is not restricted to being a constant: it may be any expression involving previously defined values, even function calls.
	* An array may be initialized by following its declaration with a list of initializers enclosed in braces and separated by commas.
    10. Recursion
		* Useful when reversing order like printing digits of an integer.
		* quicksort
	11. The C Preprocessor
		* File Inclusion
			* #include *filename*
		* Macro Substitution
			* #define max(A, B) ((A) > (B) ? (A) : (B))
			* #define dprint(expr) printf(#expr " = %g\n", expr)
			* #define paste(front, back) front ## back
		* Conditional Inclusion
			* #if
			* #endif
			* #elif
			* #else
			* #ifndef
5. Pointers and Arrays
	1. Pointers and Addresses
		* p = &c; => \*p == c
	2. Pointers and Function Arguments
		* swap(&a, &b);
	3. Pointers nad Arrays
		* In C, there is a strong relationship between pointers and arrays, strong enough that pointers and arrays should be discussed simultaneously.
			* **The pointer version will in general be faster.**
		* By definition, the value of a variable or expression of type array is the address of element zero of the array.
			* pa = &a[0]; => *pa* and *a* have identical values.
		* The name of an array (*a*) is a synonum for the location of the initial elemetn (*a[0]*).
			* pa = &a[0]; <=> pa = a;
			* => a[i] == \*(a+i)
		* In evaluating a[i], C converts it to \*(a+i); the two forms re euivalent.
			* => &a[i] == a+i
		* pa pointer => pa[i] == \*(pa+i)
		* So literally *a* pointer => a[i] == \*(a + i)
		* Then what's the difference between an array name such as *a* and a pointer such as *pa*? A pointer is a variable, so the following things are legal (which will be illegal for *a*):
			* pa = a;
			* pa++
		* When an array name (*a*) is passed to a function, what is passed is the location of the initial element (*&a[0]*).
		* As formal parameters in a function definition, the followings are equivalent:
			* char s[];
			* char \*s;   <-- **preferred**
		* It is possible to pass part of an array to a function, by passing a pointer to the beginning of the subarray.
			* f(&a[2])
			* f(a+2)
	4. Address Arithmetic
		* The symbolic constant NULL is often used in place of zero, as a mnemonic to indicate more clearly that this is a special value for a pointer.
			* NULL is defined in <stdio.h>
		* Pointers may be compared under certain circumstances.
			* If p, q point to members of the same array, then relations like ==, !=, <, >=, etc., work properly.
				* Once exception: the address of the first element past the end of an array can be used in pointer arithmetic.
		* A pointer and an integer may be added or subtraced.
			* p+n means the address of the n-th object beyond the one p currently points to.
				* This is true regardless of the kind of object p points to; n is scaled according to the size of the objects p points to, which is determined by the declaration of p.
		5. Character Pointers and Functions
			* char \*pmessage; => pmessage = "now is the time"; assigns to pmessage a pointer ro the character array. This is *not* a string copy; only pointers are involved.
				* char amessage[] = "now is the time";	/* an array \*/
				* char \*pmessage = "now is the time";	/* a pointer \*/
			* strcpy
			* strcmp
		6. Pointer Arrays; Points to Pointers
			* Array of pointers to string constants
			* In C, there is no single operation to compare/move string constants of various lengths.
			* Multiple lines can be compared and ordered not by exchanging actual lines but sorting pointers to them.
			* Pointer arrays are data representations that cope efficiently and conveniently with variable-length text lines.
			* char \*lineptr[MAXLINES];
		7. Multi-dimensional Arrays
			* vector[i][j];	/\* [row][col] /\*
			* Elements are stored by rows, so the rightmost subscript, or column, varies fastest as elements are accessed in storage order.
			* If a two-dimensional array is to be passed to a function, the parameter declaration in the function must include the number of columns; the number of rows is irrelevant, since what is passed is, as before, a pointer to an array of rows, where each row has a specific column length.
			* f(int daytab[2][13]) {...}
			* f(int daytab[][13]) {...}
			* f(int (\*daytab)[13]) {...}	/\* all the same as passing a pointer to an array of 13 integers /\*
			* More generally, only the first dimention os an array is free; all the others have to be specified.
			* f(int (\*daytab)[13][14][15]) {...}
		8. Initialization of Pointer Arrays
			* char \*name[] = {
				"Illegal month",
				"January", February"
			};
			* The compiler counts the initializers and fills in the correct number.
		9. Pointers vs. Multi-dimensional Arrays
			* int a[10][20];
			* int \*b[10];
			* Each element of b need not point to a twenty-element vector.
			* The most frequent use of arrays of pointers is to store character strings of diverse lengths.
		10. Command-line Arguments
			* In **environments** that **support C**, there is a way to **pass command-line arguments** or parameters **to a program** when it **begins executing**.
			* When *main* is called, it's called with two arguments.
				* argc	/\* argument count \*/
				* argv	/\* argument vector \*/
			* argc: the number of command-line arguments the program was invoked with.
			* argv: a pointer to an array of arguments as character strings.
			* echo hello, world!
				* argc: 3
				* argv[0]: "echo"
				* argv[1]: "hello,"
				* argv[argc-1]: "world!"
			* An **argument** that begins with a **minus sign** introduces an **optional flag** or parameter.
		11. Pointers to Functions
			* void qsort(void \*lineptr[], int left, int right, int (\*comp)(void \*, void \*));
			* (\*comp)(void \*, void \*) indicates any funciton as an argument with two pointer arguments.
			* The generic pointer type void \* is used for the arguments.
			* (int (\*)(void\*,void\*))(numeric ? numcmp : strcmp));
        12. Complicated Declarations
            * \* is a prefix operator that has lower precedence than ().
            * int \*f();    function that returns pointer to int
            * int (\*pf)(); pointer to function that returns int
    6. Structures
        1. Basics of Structures
            * struct point {
                int x;
                int y;
            };
            * struct rect {
                struct point pt1;
                struct point pt2;
            };
            * struct {
                char name[64];
                char race[64];
                char class[64];
            } x, y, z;
            * struct point pt = { 1080, 720 };
            * '.' structure operator
            * pt.x, pt.y
            * Personal note: Since I'm already familiar with class and instance from C++, my immediate question after seeing the definition of structure was to tell the difference from class in C++. Structures literally also called "records", meaning there will be no "methods" but a record of data, unlike class objects in OOP.
        2. Structures and Functions
            * struct point makepoint(int x, int y) {...}
            * struct point origin, \*pp;
            * pp = &origin;
            * pp->*member-of-structure*
                * pp->x
            * The structure operators . and ->, together with () for function calls and [] for subscripts, are at the top of the precedence hierarchy.
		3. Arrays of Structures
			* example: an array of structure { name, count } for a pre-defined dictionary and storing counts of each word occuring in a given text (using binsearch)
		4. Pointers to Structures
		5. Self-referential Structures
			* example: binary tree that keeps adding nodes as it finds a new word in a given text and keeps sorting as adding them.
		6. Table Lookup
			* example: use of hashtab in #define
		7. Typedef
			* advantages:
				* keeps data type more readible to human eyes
				* portability: if a data type is aliased with typedef, then only typedefs need to be modified when the program is moved.
		8. Unions
			* union u_tag { ... };
			* takes the largest storage space of all the member variable types, keeping the storage management more organized depending on the situation.
		9. Bit-fields
			* more human-readible ways to handle bit-fiddling for masking, flagging, etc.
	7. Input and Output
		1. Standard Input and Output
			* stdin is set to the system keyboard by default.
			* getchar() returns the next input character each time it is called, or EOF when it encounters the of file.
			* prog \<infile
			* otherprog | prog
			* stdout is set to the system monitor by default.
			* putchar(c) puts the character c on stdout. returns the character written, or EOF if an error occurs.
			* prog \>outfile
			* prog | anotherprog
		2. Formatted Output - printf
			* %-15.10s
			* sprintf(char \*string, char \*format, arg1, arg2, ...);
		3. Variable-length Argument Lists
			* int printf(char \*fmt, ...);
			* va_list ap;	points to each unnamed arg in turn
			* va_start(ap, fmt);	make app point to 1st unnamed arg
			* va_end(ap);	clean up when done
		4. Formatted Input - scanf
			* scanf, sscanf
			* if (scanf("%d %s %d", &day, monthname, &year) == 3)
			* if (scanf("%d/%d/%d", &month, &day, &year) == 3)
		5. File Access
			* FILE \*fp
			* fp = fopen("filename", "r")
			* getc(fp)
			* putc(fp)
			* formatted input or output
			* fscanf(fp, fmt, ...)
			* fprintf(fp, fmt, ...)
			* fclose(fp)
		6. Error Handling - Stderr and Exit
			* fprintf(stderr, "error!\n");
			* exit(0), exit(1), ...
			* prog 2>/dev/null
		7. Line Input and Output
			* fgets(line, maxline+1, fp)
			* fputs(line, fp)
			* gets(line) == fgets(line, , stdin)
			* puts(line) == fputs(line, stdout)
		8. Miscellaneous Functions
			1. String Operations
				* strcat: string concatenate
				* strncat: string concatenate n characters only
				* strcmp: string comparison
				* strncmp: string comparison n characters only
				* strcpy: string copy
				* strncpy: string copy n characters only
				* strlen: string length
				* strchar: character in string
				* strrchar: character in string, reverse
				* strstr: substring in string
			2. Character Class Testing and Conversion
				* isalpha
				* isupper
				* islower
				* isdigit
				* isalnum
				* isspace
				* toupper
				* tolower
			3. Ungetc
				* similar to ungetc but uses FILE instead of custom buffer
			4. Command Execution
				* system("date");
			5. Storage Management
				* void \*malloc(size_t n)
				* void \*calloc(size_t n, size_t size)	array of n objects of size size
				* ip = (int \*) calloc(n, sizeof(int));
			6. Mathematical Functions
				* sin
				* cos
				* atan2	in radians
				* exp
				* log
				* log10
				* pow
				* sqrt
				* fabs
			7. Random Number generation
				* a = rand()
				* srand(0)
	8. The UNIX System Interface
		1. File Descripters
			* More low-level I/O control than file pointers which are part of the standard C library.
			* Whenever the command interpreter (the shell) runs a program, three files are open
				* 0: stdin
				* 1: stdout
				* 2: stderr
		2. Low Level I/O - Read and Write
			* read(fd, buf, n)
				* n bytes read from fd is stored in buf
				* calling read successively reads next n bytes
				* read(0, &c, 1) reads from stdin
			* write(fd, buf, n)
				* n bytes are written into fd from buf
				* calling write successivey writes in the next n bytes
			* n = 1: unbuffered
			* n = BUFSIZ: some pre-defined number (power of 2) corresponding to a physical block size on a peripheral device.
			* static char buf[BUFSIZE]; there's nothing special about buffer. it can by any (static) character array.
		3. Open, Creat, Close, Unlink
			* fd = open(name, flags, perms);
				* flags: O_RDONLY, O_WRONLY, O_RDWR
				* perms: 0
			* fd = creat(name, perms);
				* deletes original file if it exists.
				* perms: ugo, rwx == 421
			* close(fd) ~ fclose(fp)
			* unlink(name) ~ remove: deletes the file.
		4. Random Access - Lseek
			* lseek(fd, offset, origin)
				* origin 0: offset from the beginning
				* origin 1: offset from the current position
				* origin 2: offset from the end of the file
				* returns the updated position in long (hense "long" seek) offset from the beginning
		5. Example - An implementation of Fopen and Getc
			* Example codes were too system-dependant and time-consuming for converting it into macOS, Fedora OS, and Windows 11 at the same time.
		6. Example - Listing Directories
			* Example codes were too system-dependant and time-consuming for converting it into macOS, Fedora OS, and Windows 11 at the same time.
		7. Example - A Storage Allocator
			* Example codes were too system-dependant and time-consuming for converting it into macOS, Fedora OS, and Windows 11 at the same time.
