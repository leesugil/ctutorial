#include <stdio.h>

/* Calculating the range of char, short, int, and long variables, both signed and unsigned. */

/* It might be a trivial exercise if we use
 * %u for unsigned int
 * %hu for unsigned short
 * %lu for unsigned long 
 * and print -1 in the corresponding variables. */

/* However, these don't exhaust all cases, hence the treatment of unsigned char is the challenge.
 * Since the maximum value of signed variables are the half of the range of its unsigned correspondence, the problem is reduced to calculating whether char is 1 byte or not in a given local machine. */

main ()
{
	unsigned char c = 0;
	unsigned char d = 0;
	unsigned short s = 0;
	unsigned int i = 0;
	unsigned long l = 0;

	while (s == 0) {
		d = c;
		++c;
		if (c < d) {
			c = d;
			s = 1;
		}
	}
	s = 0;

	--s;
	--i;
	--l;

	printf("Local machine's range of variables\n");
	printf("Unsigned char: from 0 to %d\nSigned char: from -%d to %d\n", c, (c-1)/2, ((c-1)/2)+1);
	printf("Unsigned short: from 0 to %hu\nSigned short: from -%hu to %hu\n", s, (s-1)/2, ((s-1)/2)+1);
	printf("Unsigned int: from 0 to %u\nSigned int: from -%u to %u\n", i, (i-1)/2, ((i-1)/2)+1);
	printf("Unsigned long: from 0 to %lu\nSigned long: from -%lu to %lu\n", l, (l-1)/2, ((l-1)/2)+1);
}
