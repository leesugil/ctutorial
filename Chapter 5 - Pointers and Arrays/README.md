## 5. Pointers and Arrays
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

