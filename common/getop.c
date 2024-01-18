#include <stdio.h>
#include <ctype.h>

int getch(void);
void ungetch(int);

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
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}
			
