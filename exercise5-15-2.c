/* This is a solution contained in the C Answer Book. I find it a nice opportunity learn a clean code from a professional. */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "getline.c"
#include "alloc.c"

#define NUMERIC	1	/* numeric sort */
#define	DECR	2	/* sort in decreasing order */
#define FOLD	4	/* fold upper and lower cases */
#define LINES	100	/* max # of lines to be sorted */

int charcmp(char *, char *);
int numcmp(char *, char *);
int readlines(char *lineptr[], int maxlines);
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *));
void writelines(char *lineptr[], int nlines, int order);

static char option = 0;

/* sort input lines */
main(int argc, char *argv[])
{
	char *lineptr[LINES];
	int nlines;
	int c, rc = 0;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0]))
			switch (c) {
				case 'f':	/* fold upper and lower cases */
					option |= FOLD;
					break;
				case 'n':	/* numeric sort */
					option |= NUMERIC;
					break;
				case 'r':	/* sort in decreasing order */
					option |= DECR;
					break;
				default:
					printf("sort: illegal option %c\n", c);
					argc = 1;
					rc = -1;
					break;
			}
	if (argc)
		printf("Usage: <codename> -fnr \n");
	else {
		if ((nlines = readlines(lineptr, LINES)) > 0) {
			if (option & NUMERIC)
				qsort2((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) numcmp);
			else if (option & FOLD)
				qsort2((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) charcmp);
			else
				qsort2((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) strcmp);
			writelines(lineptr, nlines, option & DECR);
		} else {
			printf("input too big to sort\n");
			rc = -1;
		}
	}
	return rc;
}

/* qsort2: sort v[left]...v[right] into increasing order */
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *))
{
	int i, last, mid;

	void swap(void *v[], int, int);

	if (left >= right)
		return;
	mid = (left + right) / 2;
	if ((*comp)(v[left], v[right]) > 0)
		swap(v, left, mid);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort2(v, left, last-1, comp);
	qsort2(v, last+1, right, comp);
}


#define MAXLEN 1000
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
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
		}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines, int decr)
{
	int i;

	if (decr)
		for (i = nlines-1; i >= 0; i--)
			printf("%s\n", lineptr[i]);
	else
		for (i = 0; i < nlines; i++)
			printf("%s\n", lineptr[i]);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* charcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int charcmp(char *s, char *t)
{
	for ( ; tolower(*s) == tolower(*t); s++, t++)
		if (*s == '\0')
			return 0;
	return tolower(*s) - tolower(*t);
}
