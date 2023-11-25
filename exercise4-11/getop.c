#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* Modify getop so tht it doesn't need to use ungetch. */

/* getop: get next character or numeric operand */
int getop(char s[])
{
	static int curc = -1;	/* would the initial assignment of -1 be ignored when it's called next time? */
	
	int i, c;

	if (curc == -1)
		c = getch();
	else
		c = curc;

	while((s[0] = c) == ' ' || c == '\t')
		c = getch();
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	/* not a number */
	i = 0;	/* here s[0] is already either a number or '.' */
	if (isdigit(c))	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))	/* if s[0] was already a number, collect the rest of the integer part by ++i */
			;
	if (c == '.')	/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		curc = c;
	return NUMBER;
}
