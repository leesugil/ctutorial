#include <stdio.h>

/* White a function rightrot(x, n) that retrns the value of the integer x rotated to the right by n positions */

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
	/* it seems like an easy problem if we know how many bits x has.
	 * for example, first invert x to place the 0-th bit to the highest bit.
	 * then using the knowledge of the length of x,
	 * create masks and x >> 1 to produce the output.
	 * calculating the length is mathematically possible,
	 * but i wonder if there is a better way than
	 * hard-computing the number since such algorithm
	 * would grow exponentially. */
	/* Note: looks like there's a function called sizeof.
	 * The function will be mentioned a few sections later, so
	 * I would consider using it as a soft cheating for this exercise.
	 * I'll just do the hard way now for fun. */
	int i, p;
	float y = x;

	for (p=0; y >= 2; ++p)
		y = y / 2;
	printf("%b has %d number of bits.\n", x, p+1);
	printf("%b = %b + %b\n", x, getbits(x, n-1, n) << n, getbits(x, p, p+1-n));
	x = (getbits(x, n-1, n) << p+1-n) + getbits(x, p, p+1-n);

	return x;
}

main() {
	/* code start here */
	unsigned int x = 0b1111010111110;
	int n = 4;
	unsigned z = 0b1110111101011;
	checkbits(rightrot(x, n), z);
}
