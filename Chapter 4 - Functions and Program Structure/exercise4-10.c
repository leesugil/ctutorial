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
/* An alternate organization uses getline to read an entire input line; this makes getch and ungetch unnecessary. Revise the calculator to use this approach. */
/* here one tricky part is to store the EOF info in our char [] line which is related to the previous exercise. like the previous comment, EOF is simulated in our terminal programs that doesn't exactly work like the examples in the textbook, we bypass this issue without hurting the learning experiences of the section. */
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
				printf("main: hej! this is for '+'!\n");
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
				printf("p: print top\nd: duplicate top\ns: swap top two\nc: clear stack\n@");
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


#define MAXLINE 1000

char line[MAXLINE];	/* input line */
int lp = 0;	/* input line read position */

/* getop: get next character or numeric operand */
/* since 'p', 'd', 's', 'c', and 'h' are already reserved for special commands,
 * we store values to variables by '@' followed by a letter,
 * call variable values by '#' followed by a letter. */
int getop(char s[])
{
	int i, c;
	int getline2(char [], int);

	printf("--- getop: lp = %d\n", lp);
	for (; lp < MAXLINE && (((c = line[lp]) == ' ') || c == '\t'); lp++)
		;	/* removing spaces */

	if (c == '\n' || c == '\0' || c == EOF) {
		printf("getop: the current line[lp] = '%c' with its integer value %d\n", c, c);
		/* get a new line and return ??? */
		printf("getop: getting a new line\n");
		c = getline2(line, MAXLINE);
		if (c == 0)
			return EOF;
		printf("(new line) getop: the collected line is %s\n", line);
		lp = 0;
		for (; lp < MAXLINE && (((c = line[lp]) == ' ') || c == '\t'); lp++)
			;	/* removing spaces */
	}

	for (i=0; (i < MAXOP-1) && (lp < MAXLINE) && ((c=line[lp]) != ' ') && (c != '\t') && (c != '\n') && (c != '\0') && (c != EOF); i++, lp++) {
		/* store a word to s */
		s[i] = c;
		printf("getop: i = %d, s[i] = %d which its character is '%c'.\n\tthe string s is %s\n", i, c, c, s);
	}
	printf("getop: lp stopped at %d\n", lp);
	if (i == 0 && c == '\n') {
		printf("getop: detected '\\n'\n");
		s[i++] = '\n';
		lp++;
	}
	s[i] = '\0';
	printf("(word collected) getop: the collected word is ''%s''\n", s);
	/* what if a whole word was not read? */

	int l = strlen(s);
	c = s[0];
	printf("its length is %d, and the first character is '%c'\n", l, c);

	if (c == '-' && l > 1) {
		/* '-' is understood to be a negative sign.
		* if not, atof should handle the error. */
		printf("getop: RETURN NUMBER\n");
		return NUMBER;
	}
	else if (!isdigit(c) && c != '.') {
		/* c is not a number */
		if (l == 1) {
			if (c == '@') {
				printf("getop: return VSTORE\n");
				return VSTORE;
			}
			else if (c == '#') {
				printf("getop: return VCALL\n");
				return VCALL;
			}
			else {
				printf("getop: return '%c' (arithmetic operation)\n", c);
				return c;
			}
		}
		else {
			printf("getop: return MATH\n");
			return MATH;
		}
	}
	else if (c == EOF) {
		printf("getop: EOF\n");
		return EOF;
	}
	else {
		/* c is a number. atof should handle the decimals. */
		printf("c is a number, s = %s\n", s);
		printf("getop: return NUMBER\n");
		return NUMBER;
	}
}
