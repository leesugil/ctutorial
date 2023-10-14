#include <stdio.h>

/* White a function invert(x, p, n) that returns x with the n bits that begin at position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. */

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
	/* p+1 is need to include the bit at the pth position in the output.
	 * if p=4 and n=3, the output should include the bits from p=4, 3, 2.
	 * thus amount to be shifted is, counting the number of bits,
	 * p+1 - n */
	return (x >> (p+1-n)) & ~(~0 << n);
}

/* setbits: assuming p+1 >= n, get the rightmost n bits from y and place it starting from position p in x.
 * At position p, there will be p+1 bits starting from the p-th position going down to 0.
 * Note that this is different from what I used in exercise 2-6, I think I slightly misunderstood the english instruction which the nature of the exercise didn't change much. */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	y = getbits(y, n-1, n);	/* p = n-1, n-2, ..., 0 grabs all n bits */
	y = y << p+1-n;	/* conuting, we want to have p+1-n number of zero bits */
	unsigned int m = ~0;	/* 0b...111 */
	m = m << p+1;	/* we want p+1 number of zero bits from right for masking preparation */
	m = m + ~(~0 << p+1-n);	/* we want p+1-n number of 1 bits for masking */
	x = x & m;
	x = x + y;
	return x;
}

unsigned invert(unsigned x, int p, int n)
{
	return setbits(x, p, n, ~getbits(x, p, n));
}

main() {
	/* code start here */
	unsigned int x = 0b1111010111111;
	int p = 9;
	int n = 4;
	unsigned z = 0b1110101111111;
	x = invert(x, p, n);
	checkbits(x, z);
}
