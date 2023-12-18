/* Modify the sort program to handle a -r flag, which indicates sorting in reverse (decreasing) order. Be sure that -r works with -n. */

#include <stdio.h>
#include <string.h>
#include "strcmp.c"
#include "numcmp.c"
#include "readlines.c"
#include "writelines.c"
#include "qsort.c"

#define MAXLINES 5000	/* max #lines to be sorted */
char *lineptr[MAXLINES];	/* pointers to text lines */

/* sort input lines */
main (int argc, char *argv[])
{
	int nlines;	/* number of input lines read */
	int numeric = 0;	/* 1 if numeric sort */
	int reverse = 0;	/* 1 if sorting in reverse order */

	if (argc > 1) {
		if (strcmp2(argv[1], "-r") == 0)
			reverse = 1;
		else if (strcmp2(argv[1], "-n") == 0) {
			numeric = 1;
			if (argc > 2 && strcmp2(argv[2], "-r") == 0)
				reverse = 1;
		}
	}
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort4((void**) lineptr, 0, nlines-1, reverse, (int (*)(void*, void*)) (numeric ? numcmp : strcmp2));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

