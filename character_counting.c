#include <stdio.h>

/* count characters in input; 1st version */
main()
{
	long nc;
	int c;

	nc = 0;
	printf("%d\n", putchar(EOF));
	while ((c = getchar()) != EOF) {
		putchar(c);
		++nc;
	}
	printf("%ld\n", nc);
}

