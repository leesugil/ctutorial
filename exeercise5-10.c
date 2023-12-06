/* Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. */

#include <stdio.h>
#include "getline.c"
#include "aoti.c"

#define NUMBER '0'

main(int argc, char *argv[])
{
	/* keep reading arguments until argc == 1.
	 * each time reading, use getop() to decide push/pop/etc. */
	while (--argc > 0) {
		switch((type = getop(**++argv))) {
			case NUMBER:
				push(atof(s));
				break;
			case '+':
				push(pop() + pop());
				break;
			case '*':
				push(pop() * pop());
				break;
			case '-':
				op2 = pop();
				push(pop() - op2);
				break;
			case '/':
				op2 = pop();
				if (op2 != 0.0)
					push(pop() / op2);
				else
					printf("error: zero divisor\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
	}
	return 0;
}

#define	MAXVAL	100	/* maximum depth of val stack */

int sp = 0;	/* next free stack position */
double val[MAXVAL];	/* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return op value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

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
		/* from the previous s[++i] = c != digit, the current s[i] is already a non-digit. if c == '.', then s[i] = '.' already, so it is enough to collect the rest of integers as decimal points. */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

#define	BUFSIZE	100

char buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;	/* next free position in buff */

int getch(void)	/* get a (possibly pushed-back) character */
{
	return (bufp > 0) ? buf[--bufp] : getchar();	/* beautiful */
}

void ungetch(int c)	/* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}
