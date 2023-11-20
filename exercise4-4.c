#include <stdio.h>
#include <stdlib.h>	/* for atof() */

#define	MAXOP	100	/* max size of operand or operator */
#define	NUMBER	'0'	/* signal that a number was found */

int getop(char []);
void push(double);
double pop(void);
void clear(void);

/* reverse Polish calculator */
/* Add the commands to print the op elements of the stack without popping, to duplicate it, and to swap the top two elements. Add a command to clear the stack. */
main()
{
	int type;
	double op2, op3;
	char s[MAXOP];

	printf("type 'h' for commands\n");

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
			case 'h':
				/* print commands */
				printf("p: print top\nd: duplicate top\ns: swap top two\nc: clear stack\n");
				break;
			case 'p':
				/* print top */
				push(op2 = pop());
				push(op2); /* to be popped by '\n' for print */
				break;
			case 'd':
				/* duplicate top */
				push(op2 = pop());
				push(op2);
				push(op2); /* to be popped by '\n' for print */
				break;
			case 's':
				/* swap top */
				op2 = pop();
				op3 = pop();
				push(op2);
				push(op3);
				push(op3); /* to be popped by '\n' for print */
				break;
			case 'c':
				/* clear stack */
				clear();
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

/* clear: clear the stack */
void clear(void)
{
	sp = 0;
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
	s[1] = '\0';
	i = 0;
	/* should understand the following commands:
	 * topp, topd, tops, clear */
	if (!isdigit(c) && c != '.') {
		if (c == '-') { /* handle the negative sign separately */
			if (isdigit(c = getch()) || c == '.')
				s[++i] = c; /* negative number */
			else {
				ungetch(c);
				return '-';
			}
		}
		else {
			return c;	/* not a number */
		}
	}
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
		 * then in the first loop of reading, it should just read "1" and send the remaining " " to the buffer. */
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
