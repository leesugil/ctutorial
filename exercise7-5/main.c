/* Rewrite the postfix calculator of Chapter 4 to use scanf and/or sscanf to do the input and number conversion. */

#include <stdio.h>
#include "calc.h"
#define	MAXOP	100	/* max size of operand or operator */

/* reverse Polish calculator */
int main()
{
	int type;
	double op, op2;
	char s[MAXOP];

	while ((type = getop(s)) != EOF) {
		switch (type) {
			case NUMBER:
				/*push(atof(s));*/
				sscanf(s, "%lf", &op);
				push(op);
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
