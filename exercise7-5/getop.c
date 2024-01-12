#include <stdio.h>
#include <ctype.h>
#include "calc.h"

/* getop: get next character or numeric operand */
int getop(char s[])
{
	int i, c;

	while((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	if (!isdigit(c) && c != '.')
		return c;	/* not a number */
	i = 0;	/* here s[0] is already either a number or '.' */
	if (isdigit(c))	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))	/* if s[0] was already a number, collect the rest of the integer part by ++i */
			;
	if (c == '.')	/* collect fraction part */
		/* from the previous s[++i] = c != digit, the current s[i] is already a non-digit. if c == '.', then s[i] = '.' already, so it is enough to collect the rest of integers as decimal points. */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

/* getop2: upgrades getop, uses scanf */
int getop2(char s[])
{
	double lf = 0.0;
	if (scanf("%lf", &lf) == 1) {
		/* record the number in s */
		sprintf(s, "%lf", lf);
		return NUMBER;
	} else if (scanf("%s", s) == 1)
		return s[0];
	else
		return EOF;
}
