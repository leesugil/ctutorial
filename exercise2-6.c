#include <stdio.h>

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

main() {
	/* studying bitwise operations */
	/* 8 = 1111(2), 4 = 0111(2), 2 = 0011(2), 1 = 0001(2) */

	unsigned int x = 15;
	unsigned int y = 7;

	printf("x: %u = 1111(2)\n", x);
	printf("y: %u = 0111(2)\n", y);

	printf("x >> 1: %u = 0111(2)\n", x >> 1);

	unsigned z = 010;
	printf("z: %u = 1000(2)\n", z);

	z = 012; /* 1010(2) */
	printf("z: %u = 1010(2)\n", z);
	z = z >> 1;
	printf("z >> 1: %u = 0101(2)\n", z);

	printf("What is ~0?\n");
	z = ~0;
	printf("~0: %u = 0b11111111111111111111111111111111(2)\n", z);
}
