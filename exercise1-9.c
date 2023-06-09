#include <stdio.h>

/* redundant space remover */
main()
{
	int c, b;
	b = 0;

	while ((c = getchar()) != EOF) {
		if ((b == ' ') && (c == ' '))
			;
		else
			putchar(c);
		b = c;
	}
}
