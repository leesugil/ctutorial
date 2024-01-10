#include <stdlib.h>
#include <ctype.h>
#include "atof.c"

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof2(s1);
	v2 = atof2(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

/* numcmp2: compare s1 and s2 numerically. accepts reverse */
int numcmp2(char *s1, char *s2, int reverse)
{
	/* reverse: 1 if reverse */
	double v1, v2;
	int r = 1 - 2 * reverse;

	v1 = atof2(s1);
	v2 = atof2(s2);
	if (v1 - v2 < 0)
		return -1 * r;
	else if (v1 - v2 > 0)
		return 1 * r;
	else
		return 0;
}

/* strcmp2: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp2(char *s, char *t)
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

/* strcmp3: return <0 if s<t, 0 if s==t, >0 if s>t. accepts reverse */
int strcmp3(char *s, char *t, int reverse)
{
	/* reverse: 1 if reverse */
	int output, r = 1 - 2 * reverse;

	for ( ; *s - *t == 0; s++, t++)
		if (*s == '\0')
			return 0;

	output = (*s - *t) * r;
	return output;
}
