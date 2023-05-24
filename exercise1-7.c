#include <stdio.h>

/* print the value of EOF */
main()
{
	printf("printf(EOF): %d\n", EOF);

	int c;

	while ((c = getchar()) != EOF)
		;
	printf("just purchar(EOF)");
	putchar(c);
	printf("just printf c %d\n", c);
}
