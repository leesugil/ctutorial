/* Add the option -f to fold upper and lower case together, so that case distinctions are not made during sorting; for example, a and A compare equal. */

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
	int fold = 0;	/* 1 if fold upper and lower case together */

	if (argc > 1) {
		int i;
		for (i = 1; i < argc; i++) {
			if (numeric == 0 && !strcmp2(argv[i], "-n"))
				numeric = 1;
			if (reverse == 0 && !strcmp2(argv[i], "-r"))
				reverse = 1;
			if (fold == 0 && !strcmp2(argv[i], "-f"))
				fold = 1;
		}
	}

	printf("%s comparison\n", (numeric ? "NUMERIC" : "lexiconical"));
	printf("%s order\n", (reverse ? "DESCENDING" : "ascending"));
	printf("case %ssensitive\n", (fold ? "IN" : ""));

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort5((void**) lineptr, 0, nlines-1, reverse, fold, (int (*)(void*, void*, int, int)) (numeric ? numcmp2 : strcmp3));
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("input too big to sort\n");
		return 1;
	}
}

