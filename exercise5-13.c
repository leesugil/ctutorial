/* Write the program tail, which prints the last n lines of its input. By default, n is set to 10, let us say, but it can be changed by an optional arguments so that
 * tail -n
 * prints the last n lines. The program should behave rationally no matter how unreasonable the input or the value of n. Write the program so it makes the best use of available storage; lines should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of fixed size. */

#include <stdio.h>
#include <string.h>
#include "getline.c"
#include "alloc.c"
#include "atoi.c"

#define MAXLINES 1000

int N = 10;	/* default n */
char *lineptr[MAXLINES];	/* pointers to text lines */

void setN(int argc, char *argv[]);
int readlines(char *lineptr[], int maxlines);

main(int argc, char *argv[])
{
	setN(argc, argv);

	int nlines;	/* number of lines read */

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		printf("lines read: %d\n", nlines);
		int i;
		for (i = 0; i < nlines; i++)
			printf("(original) %s\n", lineptr[i]);
		if (N > nlines)
			N = nlines;
		for (i = 0; i < N; i++)
			printf("(tail) %s\n", lineptr[nlines - N + i]);
		return 0;
	}
	else {
		printf("error\n");
		return 1;
	}
}

/* setN: set N = n when tail -n is provided. */
void setN(int argc, char *argv[])
{
	if (argc > 1)
		N = -1 * atoi(*(++argv));
}

#define MAXLEN 1000	/* max length of any input line */

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];

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
