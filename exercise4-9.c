#include <stdio.h>
#include <stdlib.h>	/* for atof() */
#include <ctype.h>	/* for isdigit() */
#include <math.h>	/* for some systems, requires -lm when compiling */
#include <string.h>	/* for strlen() */

#define	MAXOP	100	/* max size of operand or operator */
#define	NUMBER	'0'	/* signal that a number was found */
#define MATH	'1'	/* signal that math library is called */
#define VSTORE	'2'	/* signal to store a variable value */
#define VCALL	'3'	/* signal to call a cariable value */

int getop(char []);
void push(double);
double pop(void);
void clear(void);
void math(char []);
void vstore(char []);
void vcall(char []);

/* reverse Polish calculator */
/* Our getch and ungetch do not handle a pushed-back EOF correctly. Decide what their properties ought to be if an EOF is pushed back, then implement your design. */
/* comment: in the original code, here's how EOF is handled.
* if the buffer is empty and ctrl+D (for EOF) is provided,
* getop returns it to the while loop in main() which breaks the loop.
* if the buffer is not empty like the following line, for example:
* "1 3 5 + (ctrl+D)"
* then since getop just returns EOF without saving it to the buffer,
* and the buffer is left without the EOF part, and getchar() runs immediately.
* (this doesn't get displayed properly in the command line.) 
* so the design should be updated so that, even if EOF is provided in the middle of input stream, the program should close at where EOF occurs.
* now storing EOF in buffer is the main goal.
* note that the integer value of EOF is -1, whereas char has the 0-255 range in my device. */
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
			case MATH:
				math(s);
				break;
			case VSTORE:
				vstore(s);
				printf("\tvariable stored\n");
				break;
			case VCALL:
				vcall(s);
				printf("\tvariable called\n");
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
				/* variable 'o' is reserved for the most recently printed value */
				vstore("@o");
				printf("\t%.8g\n", op2 = pop());
				vcall("#o");
				printf("\tstored value: %.8g\n", pop());
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

void math(char s[])
{
	double tmp;
	int l = strlen(s);

	if (l == 3)
		if (s[0] == 's' && s[1] == 'i' && s[2] == 'n')
			push(sin(pop()));
		else if (s[0] == 'c' && s[1] == 'o' && s[2] == 's')
			push(cos(pop()));
		else if (s[0] == 'e' && s[1] == 'x' && s[2] == 'p')
			push(exp(pop()));
		else if (s[0] == 'p' && s[1] == 'o' && s[2] == 'w') {
			tmp = pop();
			push(pow(pop(), tmp));
		}
		else
			printf("error: unknown math command\n");
	else
		printf("error: unknown math command\n");
}

/* twenty-six variables with single-letter names */
#define MAXVAR	26
double var[MAXVAR];

/* vstore: stores the top stack value to the designated variable */
void vstore(char s[])
{
	double c;

	if (s[0] == '@')
		if ('a' <= s[1] && s[1] <= 'z') {
			var[s[1] - 'a'] = c = pop();
			push(c);
		}
		else
			printf("error: unknown variable name\n");
	else
		printf("error: unknown variable store command\n");
}

/* vcall: pushes a stored variable value */
void vcall(char s[])
{
	if (s[0] == '#') {
		if ('a' <= s[1] && s[1] <= 'z')
			push(var[s[1] - 'a']);
		else
			printf("error: unknown variable name\n");
	}
	else
		printf("error: unknown variable call command\n");
}


int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
/* since 'p', 'd', 's', 'c', and 'h' are already reserved for special commands,
 * we store values to variables by '@' followed by a letter,
 * call variable values by '#' followed by a letter. */
int getop(char s[])
{
	int i, c, sign;

	/* read the fisrt non-space character */
	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';
	i = 0;
	if (c == '@') {
		if ('a' <= (c = getch()) && c <= 'z') {
			s[1] = c;
			s[2] = '\0'; /* s == "@x" */
			return VSTORE;
		}
		else
			ungetch(c);
	}
	if (c == '#') {
		if ('a' <= (c = getch()) && c <= 'z') {
			s[1] = c;
			s[2] = '\0'; /* s == "#x" */
			return VCALL;
		}
		else
			ungetch(c);
	}
	if (c == EOF)
		printf("getop: first EOF check\n");
	if (!isdigit(c) && c != '.') {
		if (c == EOF)
			printf("getop: second EOF check\n");
		if (c == '-') { /* handle the negative sign separately */
			if (isdigit(c = getch()) || c == '.')
				s[++i] = c; /* negative number */
			else {
				ungetch(c);
				return '-';
			}
		}
		else if ('a' <= c && c <= 'z') {
			while ((s[++i] = c = getch()) != ' ' && c != '\t' && c != '\n' && c != EOF)
				;
			s[i] = '\0';
			ungetch(c);
			if (i > 2)
				return MATH;
			else
				return s[0];
		}
		else {
			if (c == EOF)
				printf("getop: third EOF check, c == EOF: %d\n", c);
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
	if (c == EOF)
		printf("getop: fourth EOF check\n");
	ungetch(c);
	return NUMBER;
}

#define	BUFSIZE	100

int buf[BUFSIZE];	/* buffer for ungetch */
int bufp = 0;	/* next free position in buff */

int getch(void)	/* get a (possibly pushed-back) character */
{
	/* return (bufp > 0) ? buf[--bufp] : getchar();	beautiful */
	if (bufp > 0)
		return buf[--bufp];
	else {
		printf("getch: buf empty, running getchar\n");
		return getchar();
	}
}

void ungetch(int c)	/* push character back on input */
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
	int i = 0;
	printf("ungetch: buf: ");
	while (i++ < BUFSIZE)
		printf("[%c, %d], ", buf[i], buf[i]);
	printf("\n");
}

/* ungets: push back an entire string onto the input. */
void ungets(char s[])
{
	/* the string characters should be stored in buf in reserse order (LIFO) */
	int l = strlen(s);
	
	while (l > 0)
		ungetch(s[--l]);
}
