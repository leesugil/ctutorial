#include <stdio.h>
#include <string.h>
#include "getline.c"
#include "alloc.c"

#define MAXLEN 1000	/* max length of any input line */

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

	printf("(readlines) Provide line inputs, EOF to end.\n");
	nlines = 0;
	while ((len = getline2(line, MAXLEN)) > 0)
		if (nlines >= maxlines || (p = alloc(len)) == NULL)
			return -1;
		else {
			line[len-1] = '\0';	/* delete newline */
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}
