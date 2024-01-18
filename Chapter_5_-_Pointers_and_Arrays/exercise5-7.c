#include <stdio.h>
#include <string.h>
#include "./getline.c"
#include "./alloc.c"
#include "./qsort.c"
#include "./strcpy.c"

#define MAXLINES 5	/* max #lines to be sorted */
#define MAXLEN 10 /* max length of any input line */

char *lineptr[MAXLINES];	/* pointers to text lines */

int readlines(char *lineptr[], int maxlines, char alllines[], int maxchars);
void writelines(char *lineptr[], int nlines);

void qsort2(char *lineptr[], int left, int right);

/* sort input lines */
main()
{
	int nlines;	/* number of input lines read */
	int MAXCHAR = MAXLINES * MAXLEN;
	char alllines[MAXCHAR];

	if ((nlines = readlines(lineptr, MAXLINES, alllines, MAXCHAR)) >= 0) {
		qsort2(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: input to big to sort\n");
		return 1;
	}
}

int getline2(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char alllines[], int maxchars)
{
	int len, nlines, i = 0;
	char *p, line[MAXLEN];

	p = alllines;
	while ((len = getline2(line, MAXLEN)) > 0)
		if (nlines >= maxlines || p - alllines + len >= maxchars)
			return -1;
		else {
			line[len-1] = '\0';	/* delete newline */
			strcpy2(p, line);
			printf("...readlines: storing a line: line: %s\talllines: %s\n", line, alllines);
			lineptr[nlines++] = p;
			p += len;
		}
	printf("...readlines: alllines: %s\n", alllines);
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;

	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}
