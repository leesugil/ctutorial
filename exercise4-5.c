#include <stdio.h>
#include <stdlib.h>	/* for atof() */
#include <math.h>	/* for math library functions */

#define	MAXOP	100	/* max size of operand or operator */
#define	NUMBER	'0'	/* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);

/* reverse Polish calculator */
/* Add access to library functions like sin, exp, and pow */
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
				op2 = pop();
				if (op2 != 0.0)
					push(((int) pop()) % ((int) op2));
				else
					printf("error: modulo zero!\n");
				break;
			case '\n':
				printf("\t%.8g\n", pop());
				break;
			default:
				printf("error: unknown command %s\n", s);
				break;
		}
		printf("getop done!\n");
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

/* ptop: print the top element without popping */
double ptop(void)
{
	if (sp > 0)
		return val[sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* dtop: duplicate the top element */
void dtop(void)
{
	if (sp > 0)
		push(ptop());
	else
		printf("error: stack empty\n");
}

/* swap: swap the top two elements */
void swap(void)
{
	double op1, op2;

	if (sp > 1) {
		op2 = pop();
		op1 = pop();
		push(op2);
		push(op1);
	}
	else
		printf("error: stack too low to swap\n");
}

/* clear: clear the stack */
void clear(void)
{
	sp = 0;
	val[sp] = 0.0;
}

#include <ctype.h>

int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
	int i, c, sign;

	while((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	printf("initial s: %s\n", s);
	i = 0;
	if (c != '-' && !isdigit(c) && c != '.') {
		/* collect string operator */
		while ('A' <= (s[++i] = c = getch()) && c <= 'z')
			;
		s[i] = '\0';
		return c;	/* not a number */
	}
	if (c == '-')	/* get ready to collect digits */
		s[++i] = c = getch();
	if (isdigit(c))	/* collect integer part */
		while (isdigit(s[++i] = c = getch()))
			printf("integer part: %d\n", c - '0');
	if (c == '.')	/* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			printf("fraction part: %d\n", c - '0');
	s[i] = '\0';
	printf("terminal s: %s\n", s);
	if (c != EOF) {
		ungetch(c);
		printf("c != EOF, c: %d\n", c);
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
