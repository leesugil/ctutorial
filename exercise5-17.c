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
#include "getline.c"
#include "alloc.c"

#define NUMERIC	1	/* 0001 numeric sort */
#define	DECR	2	/* 0010 sort in decreasing order */
#define FOLD	4	/* 0100 fold upper and lower cases */
#define DIREC	8	/* 1000 directory order */
#define LINES	100	/* max # of lines to be sorted */
#define runqsort(x, p, y, z, q) (qsort2((void **) p, 0, nlines-1, (int (*)(void *, void *, int)) x, y, z, q))

int foldcmp(char *, char *);
int numcmp(char *, char *);
int dircmp(char *, char *);
int strcmp2(char *, char *, int);
int readlines(char *lineptr[], int maxlines);
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *, int), int, int, void *w[]);
void writelines(char *lineptr[], int nlines, int order);

static int option = 0;	/* now int instead of char to hold up to the number of bytes an integer variable can hold in the system */
static int field = 0;

/* sort input lines */
int main(int argc, char *argv[])
{
	char *lineptr[LINES];
	int nlines;
	int c, rc = 0;

	while (--argc > 0 && (*++argv)[0] == '-' && ++field > 0)
		while ((c = *++argv[0]))
			switch (c) {
				case 'd':	/* directory order */
					option |= (DIREC + (field - 1) * 8);
					break;
				case 'f':	/* fold upper and lower cases */
					option |= (FOLD + (field - 1) * 8);
					break;
				case 'n':	/* numeric sort */
					option |= (NUMERIC + (field - 1) * 8);
					break;
				case 'r':	/* sort in decreasing order */
					option |= (DECR + (field - 1) * 8);
					break;
				default:
					printf("sort: illegal option %c\n", c);
					argc = 1;
					rc = -1;
					break;
			}
	printf("accepted option(s): %x, %d field(s)\n", option, field);
	if (argc)
		printf("Usage: <codename> -fnrd \n");
	else {
		/* sort must be done multiple times, hence changes here */
		/* since it's a proptype, we assume the field sorting is always done starting from the initial field to subsequent fields */
		/* to each comparison function, we provide the field number to work on as well which to the corresponding changes should be made in the function later in this work. */
		if ((nlines = readlines(lineptr, LINES)) > 0) {
			while (field > 0) {
				/* this code also should turn back to the original idea with option & FOLD and option & DIREC showing up clearly in here */
				/* in order for this to work, especially making FOLD and DIREC interchangeably used, should i make a copy of the original lines that's allowed to be modified such as masking certain characters for comparisons without hurting the original?
				 * also, even if i do that, in which order FLD and DIREC sort should appear in here, if it's ever appropriate with the if-elif structure? */
				char *linestocompare[LINES];
				if (option & (FOLD + (field - 1) * 8))
					;	/* determine whether to use the original lineptr or the tolower(*) version of it */
				if (option & (NUMERIC + (field - 1) * 8))
					runqsort(numcmp, lineptr, option, field--, linestocompare);
				else if (option & (DIREC + (field - 1) * 8))
					runqsort(dircmp, lineptr, option, field--, linestocompare);
				else
					runqsort(strcmp2, lineptr, option, field--, linestocompare);
			}
			printf("\n\n(sort) Printing Output...\n\n");
			writelines(lineptr, nlines, option & DECR);
		} else {
			printf("input too big to sort\n");
			rc = -1;
		}
	}
	return rc;
}

/* qsort2: sort v[left]...v[right] into increasing order */
void qsort2(void *v[], int left, int right, int (*comp)(void *, void *, int), int option, int field, void *w[])
{
	/* compare lines in w, swap v as swapping w */
	int i, last, mid;

	void swap(void *v[], int, int);

	if (left >= right)
		return;
	mid = (left + right) / 2;
	if ((*comp)(w[left], w[right], option) > 0) {
		swap(v, left, mid);
		swap(w, left, mid);
	}
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(w[i], w[left], option) < 0) {
			swap(v, ++last, i);
			swap(w, last, i);
		}
	swap(v, left, last);
	swap(w, left, last);
	qsort2(v, left, last-1, comp, option, w);
	qsort2(v, last+1, right, comp, option, w);
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

/* foldcmp: return <0 if s<t, 0 if s==t, >0 if s>t */
int foldcmp(char *s, char *t)
{
	for ( ; tolower(*s) == tolower(*t); s++, t++)
		if (*s == '\0')
			return 0;
	return tolower(*s) - tolower(*t);
}

/* dircmp: compares only letters, numbers, and blanks.
 * compatiable with -f
 * returns <0 if s<t, 0 if s==t, >0 if s>t */
int dircmp(char *s, char *t)
{
	/* deprecated */
	return 0;
}

/* strcmp2: returns <0 if s<t, 0 if s==t, >0 if s>t
 * accepts option for -fd */
int strcmp2(char *s, char *t, int option)
{
	char a, b;	/* characters to compare depending on the option */
	int f = option & FOLD;	/* 1 if fold */
	int d = option & DIREC;	/* 1 if directory order */

	for ((a = d ? ((isalnum(*s) || *s == ' ' || *s == '\0') ? (*s) : (' ')) : (*s)), b = (d ? ((isalnum(*t) || *t == ' ' || *t == '\0') ? (*t) : (' ')) : (*t));\
			f ? (tolower(a) == tolower(b)) : (a == b);\
			s++, t++, a = d ? ((isalnum(*s) || *s == ' ' || *s == '\0') ? (*s) : (' ')) : (*s), b = d ? ((isalnum(*t) || *t == ' ' || *t == '\0') ? (*t) : (' ')) : (*t))
		if (*s == '\0')
			return 0;
	return (f) ? (tolower(*s) - tolower(*t)) : (*s - *t);
}