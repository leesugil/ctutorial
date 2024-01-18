/* Add a field-searching capability, so sorting may be done on fields within lines, each field sorted according to an independant set of options. (The index for this book was sorted with -df for the index category and -n for the page numbers.) */

/* Example: csv
 *
 * Input:
 * %B,3
 * *b,3
 * &a,4
 * *A,2
 * @C,3
 * #c,4
 *
 * Command: -df for index category, -n for page numbers
 *
 * Output:
 * *A,2
 * &a,4
 * *b,3
 * %B,3
 * @C,3
 * #c,4
 * */


#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include "getline.c"
#include "alloc.c"

#define NUMERIC	1	/* 0001 numeric sort */
#define	DECR	2	/* 0010 sort in decreasing order */
#define FOLD	4	/* 0100 fold upper and lower cases */
#define DIREC	8	/* 1000 directory order */
#define LINES	100	/* max # of lines to be sorted */
#define MAXLEN 1000
#define runqsort(x, p, q) (qsort2((void **) p, 0, nlines-1, (int (*)(void *, void *)) x, (void **) q))

int numcmp(char *, char *);
int strcmp2(char *, char *);
int readlines(char *lineptr[], int maxlines);
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *), void *w[]);
void writelines(char *lineptr[], int nlines);
void capturefield(char *v[], char *w[], int field, int size);
void foldlines(char *v[], int size);
void dirlines(char *v[], int size);
void descend(char *v[], int size);

static int option = 0;	/* now int instead of char to hold up to the number of bytes an integer variable can hold in the system */
static int field = 0;

/* sort input lines */
int main(int argc, char *argv[])
{
	char *lineptr[LINES];
	int nlines;
	int c, rc = 0;
	int fieldsort = 1;

	while (--argc > 0 && (*++argv)[0] == '-') {
		option <<= 4;	/* the left most half-byte will represent the option for the first field */
		/* the right most 4-bits are the option for the right most field */
		field++;
		while ((c = *++argv[0]))
			switch (c) {
				case 'd':	/* directory order */
					option |= DIREC;
					break;
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
	}
	if (argc)
		printf("Usage: <codename> -fnrd -fnrd ... CSV support only\n");
	else {
		if ((nlines = readlines(lineptr, LINES)) > 0) {
			while (field >= 0 && fieldsort == 1) {
				char *linestocompare[nlines];
				capturefield(lineptr, linestocompare, field, nlines);
				if (option & FOLD)
					foldlines(linestocompare, nlines);
				if (option & DIREC)
					dirlines(linestocompare, nlines);

				if (option & NUMERIC)
					runqsort(numcmp, lineptr, linestocompare);
				else
					runqsort(strcmp2, lineptr, linestocompare);

				if (option & DECR)
					descend(lineptr, nlines);

				if (field == 1)
					fieldsort = 0;
				field--;
				option >>= 4;
				printf("\n(sort) ...Printing interim output...\n");
				writelines(lineptr, nlines);
			}
			printf("\n(sort) Printing Output...\n");
			writelines(lineptr, nlines);
		} else {
			printf("input too big to sort\n");
			rc = -1;
		}
	}
	return rc;
}

/* capturefield: from v array of pointers to CSV, captures the field'th field and store a pointer to it in w */
void capturefield(char *v[], char *w[], int field, int size)
{
	/* this is currently not capturing n'th field correctly */
	/* if field == 0, capture the whole line ignoring commas
	 * if field == 1, respect the csv format */
	int i, j, k, f = field;
	char c, *p, line[MAXLEN];
	for (i = 0; i < size; i++) {
		for (j = 0, k = 0; (c = v[i][j]) != '\0'; j++) {
			if (f == 0)
				line[k++] = c;
			else if (f == 1) {
				if (c == ',')
					break;
				else
					line[k++] = c;
			}
			else if (c == ',')
				f--;
		}
		line[k] = '\0';
		if ((p = alloc(MAXLEN)) == NULL)
			printf("(capturefield) Out of memory!\n");
		else {
			strcpy(p, line);
			w[i] = p;
			printf("(capturefield) w[%d] = %s\n", i, w[i]);
		}
		f = field;
	}
}

/* foldlines: convert strings to lower cases */
void foldlines(char *v[], int size)
{
	int i, j;
	for (i = 0; i < size; i++)
		for (j = 0; v[i][j] != '\0'; j++)
			v[i][j] = tolower(v[i][j]);
}

/* dirlines: convert strings to directory order form */
void dirlines(char *v[], int size)
{
	int i, j;
	char c;
	for (i = 0; i < size; i++)
		for (j = 0; (c = v[i][j]) != '\0'; j++)
			if (!isalnum(c) && c != ' ')
				v[i][j] = ' ';
}

/* descend: change ascending order to descending */
void descend(char *v[], int size)
{
	int i;
	char *p;

	for (i = 0; i < size/2; i++) {
		if ((p = alloc(MAXLEN)) == NULL)
			printf("(descend) Out of memory!\n");
		else {
			strcpy(p, v[i]);
			v[i] = v[size - 1 - i];
			v[size - 1 - i] = p;
		}
	}
}

/* qsort2: sort v[left]...v[right] into increasing order */
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *), void *w[])
{
	/* compare lines in w, swap v as swapping w */
	int i, last, mid;

	void swap(void *v[], int, int);

	if (left >= right)
		return;
	mid = (left + right) / 2;
	printf("(qsort2)__initial__ left: v[%d] = \"%s\", mid: v[%d] = \"%s\", right: v[%d] = \"%s\"\n", left, v[left], mid, v[mid], right, v[right]);
	if ((*comp)(w[mid], w[left]) < 0)
		for (i = mid - 1; i >= left; i--) {	/* (1) */
			printf("(qsort2) \tplacing basis to the left position: v[%d] = \"%s\" and v[%d] = \"%s\"\n", i, v[i], i+1, v[i+1]);
			swap(v, i, i + 1);
			swap(w, i, i + 1);
		}
	printf("(qsort2)__initial swap__ left: v[%d] = \"%s\", mid: v[%d] = \"%s\", right: v[%d] = \"%s\"\n", left, v[left], mid, v[mid], right, v[right]);
	last = left;
	for (i = left+1; i <= right; i++)	/* (2) */
		if ((*comp)(w[i], w[left]) < 0) {
			printf("(qsort2) \t\tw[i] < w[left], swapping v[%d] = \"%s\" and v[%d] = \"%s\"\n", i, v[last+1], i, v[i]);
			swap(v, ++last, i);
			swap(w, last, i);
			printf("(qsort2) \t\t...swapped result: v[%d] = \"%s\" and v[%d] = \"%s\"\n", last, v[last], i, v[i]);
		}
	for (i = left; i < last; i++) {	/* error here? */
		printf("(qsort2) \trestoring the basis to the new \"mid\" position: v[%d] = \"%s\" and v[%d] = \"%s\"\n", i, v[i], i+1, v[i+1]);
		swap(v, i, i + 1);
		swap(w, i, i + 1);
	}
	printf("(qsort2)__terminal__ left: v[%d] = \"%s\", last: v[%d] = \"%s\", right: v[%d] = \"%s\"\n", left, v[left], last, v[last], right, v[right]);
	qsort2(v, left, last-1, comp, w);
	qsort2(v, last+1, right, comp, w);
}

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
void writelines(char *lineptr[], int nlines)
{
	int i;

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

/* strcmp2: returns <0 if s<t, 0 if s==t, >0 if s>t
 * accepts option for -fd */
int strcmp2(char *s, char *t)
{
	for (; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}
