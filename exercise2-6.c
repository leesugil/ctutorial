#include <stdio.h>

/* White a function setbits(x, p, n, y) that returns x with the n bits that begin at position p set to the rightmost n bits of y, leaving the other bits unchanged.
 * The English here was a bit confusing to me, so here's my paraphrased goal of the exercise:
 * 1) Take the rightmost n bits of y
 * 2) Overwrite the left n bits of x starting at position p */

/* Note that clearly I was confused with English here, the solution to Exercise 2-7 also fixes setbits for its intended use. */

/* getbits: get n bits from position p where p=0 is the first rightmost position. */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	printf("setbits(x, p, n, y)\n");
	printf("x=%u == 0b111111111111 %d\n", x, x == 0b111111111111);
	printf("y=%u == 0b111111100010 %d\n", y, y == 0b111111100010);
	printf("p=%d, n=%d\n", p, n);
	y = getbits(y, n-1, n);
	printf("y=%u == 0b100010 %d\n", y, y == 0b100010);
	y = y << p;
	printf("y=%u == 0b10001000000000 %d\n", y, y == 0b10001000000000);
	printf("Insert this to x to produce the outcome.\n");
	printf("Preparing for masking 0's between p-th and (p+n)-th bits in x.\n");
	unsigned int m = ~0;
	m = m << n+p;
	printf("~m=%u == 0b11111111111111 %d\n", ~m, ~m == 0b11111111111111);
	m = m + ~(~0 << p);
	printf("~m=%u == 0b11111100000000 %d\n", ~m, ~m == 0b11111100000000);
	x = x & m;
	printf("x: %u == 0b11111111 %d\n", x, x == 0b11111111);
	x = x + y;
	printf("x: %u == 0b10001011111111 %d\n", x, x == 0b10001011111111);
	return x;
}

main() {
	/* studying bitwise operations */
	/* 8 = 1111(2), 4 = 0111(2), 2 = 0011(2), 1 = 0001(2) */

	unsigned int a = 15;
	unsigned int b = 7;

	printf("a: %u = 1111(2)\n", a);
	printf("b: %u = 0111(2)\n", b);

	printf("a >> 1: %u = 0111(2)\n", a >> 1);

	unsigned c = 010;
	printf("c: %u = 1000(2)\n", c);

	c = 012; /* 1010(2) */
	printf("c: %u = 1010(2)\n", c);
	c = c >> 1;
	printf("c >> 1: %u = 0101(2)\n", c);

	printf("What is ~0?\n");
	c = ~0;
	printf("~0: %u = 0b11111111111111111111111111111111(2)\n", c);

	/* beginning of actual code */
	printf("Exercise code starts here.\n");

	unsigned int x = 0b111111111111;
	unsigned int y = 0b111111100010;
	int p = 9 - 1;
	int n = 6;
	unsigned int z = 0b10001011111111;
	unsigned int output;

	printf("x=%u : 0b111111111111, %d\n", x, x == 0b111111111111);
	printf("y=%u : 0b111111100010, %d\n", y, y == 0b111111100010);
	printf("p=9, n=6\n");
	output = setbits(x, p, n, y);

	printf("output=%u: 0b10001011111111, %d\n", output, output == z);
}
