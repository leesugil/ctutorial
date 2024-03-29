## 2. Types, Operators and Expressions
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
