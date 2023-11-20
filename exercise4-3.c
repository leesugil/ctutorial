#include <stdio.h>
#include <stdlib.h>	/* for atof() */

#define	MAXOP	100	/* max size of operand or operator */
#define	NUMBER	'0'	/* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
/* Add the modulus (%) operator and provisions for negative numbers */
main()
{
	int type;
	double op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
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
			case '%':
				op2 = (int) pop();
				if (op2 != 0)
					push(((int) pop()) % ((int) op2));
				else
					printf("error: zero modulo\n");
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
	int i, c, sign;

	/* read the fisrt non-space character */
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	/*s[1] = '\0'; finish reading after reading only one first non-space character.
	 * this is from the original code, and would work well if the first character is all we need to read.
	 * however, this wouldn't be sufficient to check if the first read '-' would mean an operator or a negative sign followed by digits.
	 * it is necessary to read the next character to determine it.
	so here's the plan:
	1) read up to two character slots
	2) if s[0] is '-', determine if it's an operator or a negative sign
	3) proceed as original */
	printf("c == %c, s[0] == %c\n", c, s[0]);
	s[1] = '\0';
	if (!isdigit(s[0]) && s[0] != '.') {
		printf("s[0] == %c, c == %c\n", s[0], c);
		return c;
	}
	i = 0;
	if (isdigit(c))	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			;
	if (c == '.')	/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;
	s[i] = '\0';
	if (c != EOF) {
		/* sending the remaining line to the buffer.
		 * for example, if the input line was
		 * "1 2 +\nEOF",
		 * then in the first loop of reading, it should just read "1 " and send the remaining "2 +\nEOF" to the buffer. */
		printf("ungetting\n");
		ungetch(c);
	}
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
