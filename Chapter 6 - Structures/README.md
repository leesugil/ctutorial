## 6. Structures
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
