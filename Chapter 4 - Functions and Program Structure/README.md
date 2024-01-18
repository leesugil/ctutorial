## 4. Functions and Program Structure
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
