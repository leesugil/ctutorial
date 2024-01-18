/* Write the program expr, which evaluates a reverse Polish expression from the command line, where each operator or operand is a separate argument. */

#include <stdio.h>
#include "getline.c"
#include "atof.c"

#define NUMBER '0'

int getop2(char []);
void push(double);
double pop(void);

main(int argc, char *argv[])
{
	int op2;
	/* keep reading arguments until argc == 1.
	 * each time reading, use getop() to decide push/pop/etc. */
	if (argc > 1) {
		while (--argc > 0) {
			switch(getop2(*++argv)) {	/* need a way to understand '\n'. */
				case NUMBER:
					push(atof(*argv));
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
				default:
					printf("error: unknown command %s\n", *argv);
					break;
			}
		}
		printf("\t%.8g\n", pop());
	}
	return 0;
}

#define	MAXVAL	100	/* maximum depth of val stack */

int sp = 0;	/* next free stack position */
double val[MAXVAL];	/* value stack */

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL) {
		val[sp++] = f;
		printf("(push) pushing %g to %d in val\n", f, sp - 1);
	}
	else
		printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return op value from stack */
double pop(void)
{
	if (sp > 0) {
		printf("(pop) popping at %d\n", sp - 1);
		return val[--sp];
	}
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

/* getop2: get next character or numeric operand */
int getop2(char s[])
{
	int c;

	c = s[0];
	if (!isdigit(c) && c != '.') {
		printf("(getop2) returning a non-number.\n");
		return c;	/* not a number */
	}
	else {
		printf("(getop2) returning a number.\n");
		return NUMBER;
	}
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
