#include <stdio.h>

/* White a function invert(x, p, n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. */

/* getbits: get n bits from position p where p=0 is the first rightmost position. */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

/* setbits: get the rightmost n bits from y and place it starting from position p in x */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	y = getbits(y, n-1, n);
	y = y << p;
	unsigned int m = ~0;
	m = m << n+p;
	m = m + ~(~0 << p);
	x = x & m;
	x = x + y;
	return x;
}

main() {
	/* code start here */
}
