#include <stdlib.h>
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

/* numcmp2: compare s1 and s2 numerically. accepts reverse, fold */
int numcmp2(char *s1, char *s2, int reverse, int fold)
{
	/* reverse: 1 if reverse
	 * fold: doesn't do anything here but for the simplicity of the main code */
	double v1, v2;

	v1 = atof2(s1);
	v2 = atof2(s2);
	if (v1 - v2 < 0)
		return -1 * (1 - 2 * reverse);
	else if (v1 - v2 > 0)
		return 1 * (1 - 2 * reverse);
	else
		return 0;
}
