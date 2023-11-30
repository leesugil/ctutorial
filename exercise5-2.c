#include <stdio.h>
#include <ctype.h>
#include "./calc/getch.c"

/* Write getfloat, the floating-point analog of getint. What type does getfloat return as its function value? */

/* getfloat: get next floating number from input into *pn */
int getfloat(float *pn)
{
	extern int getch(void);
	extern void ungetch(int);
	int c, sign, power;

	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);	/* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	/* collect integer part */
	for (*pn = 0.0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	/* collect decimal part */
	if (c == '.') {
		c = getch();
		for (power = 1; isdigit(c); c = getch()) {
			*pn = 10 * *pn + (c - '0');
			power *= 10;
		}
		*pn /= power;
	}
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define SIZE 10

main()
{
	int n, getfloat(float *);
	float array[SIZE];

	for (n = 0; n < SIZE; n++)
		array[n] = 0.0;

	for (n = 0; n < SIZE && getfloat(&array[n]) != EOF; n++)
		printf("array[%d] = %f\n", n, array[n]);
}
