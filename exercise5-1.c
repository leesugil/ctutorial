#include <stdio.h>
#include <ctype.h>
#include "./calc/getch.c"

#define SIZE 10

/* As written, getint treats a + or - not followed by a digit as a valid representation of zero. Fix it to push such a character back on the input. */

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign, s;

	extern int getch(void);
	extern void ungetch(int);

	while (isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-') {
		s = c;
		if (!isdigit(c = getch())) {
			/* it is not a number */
			ungetch(s);
			if (c != EOF)
				ungetch(c);
			return 0;
		}
	}
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

main()
{
	int n, array[SIZE], getint(int *);

	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
		printf("array[%d] = %d\n", n, array[n]);
}
