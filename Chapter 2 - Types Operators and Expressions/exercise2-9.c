#include <stdio.h>

/* Write a faster version of bitcount using the hint that, in a two's complement number system, x &= (x-1) deletes the rightmost 1-bit in x. */

/* checkbits: compares to unsigned integers */
void checkbits(unsigned x, unsigned y)
{
	if (x == y)
		printf("%b == %b\n", x, y);
	else
		printf("%b != %b\n", x, y);
}

/* getbits: get n bits from position p where p=0 is the first rightmost position. */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

/* setbits: get the rightmost n bits from y and place it starting from position p in x. */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	y = getbits(y, n-1, n);
	y = y << p+1-n;
	unsigned int m = ~0;
	m = m << p+1;
	m = m + ~(~0 << p+1-n);
	x = x & m;
	x = x + y;
	return x;
}

/* invert(x, p, n) returns x with the n bits that begin at position p inverted, leaving the others unchanged. */
unsigned invert(unsigned x, int p, int n)
{
	return setbits(x, p, n, ~getbits(x, p, n));
}

/* rightrot(x, n) returns the value of the integer x rotated to the right by n positions. */
unsigned rightrot(unsigned x, int n)
{
	int i, p;
	float y = x;

	for (p=0; y >= 2; ++p)
		y = y / 2;
	printf("%b has %d number of bits.\n", x, p+1);
	printf("%b = %b + %b\n", x, getbits(x, n-1, n) << n, getbits(x, p, p+1-n));
	x = (getbits(x, n-1, n) << p+1-n) + getbits(x, p, p+1-n);

	return x;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
	int b;

	for (b=0; x != 0; x >>= 1) {
		printf("%d\t%b\n", b, x);
		if (x & 01)
			b++;
	}
	printf("%d\t%b\n", b, x);
	return b;
}

/* bitcount2: a faster version of bitcount */
int bitcount2(unsigned x)
{
	int n = 0;

	printf("%d\t%b\n", n, x);
	while (x != 0) {
		x &= (x-1);
		++n;
		printf("%d\t%b\n", n, x);
	}

	return n;
}

main() {
	/* code start here */
	unsigned long int x = 0b10101011110101010010100011101010011100110001110111010101000;
	printf("x: %b\n", x);
	printf("x-1: %b\n", x-1);
	printf("x & (x-1): %b\n", x & (x-1));
	printf("bitcount result: %d\n", bitcount(x));
	printf("bitcount2 result: %d\n", bitcount2(x));
}
