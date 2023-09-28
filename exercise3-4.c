#include <stdio.h>
#include <string.h>

#define	MAXLINE	1000

/* In a two's complement number representation (like -128 to 127), our version of itoa does not handle the largest negative number, that is, the value of n equal to -(2^(wordsize-1)). Explain why not. Modify it to print that value correctly, regardless of the machine on which it runs. */

/* itoa: convert n to characters in s */
void itoa(int n, char s[]);
/* Suppose we have a two's complement system with the integer size 32 so that int ranges between -2,147,483,648 to 2,147,483,647.
 * If n = -2147483648, -n = 2147483648 = 2147483647 + 1 which is out of range of positive integer by 1. This gives -n = n, as -2147483648 is the next number to 2147483647 under the modulo 2^32.
 * Then -n % 10 gives -8, and -8 + '0' gives '(' which fuckes all up. */
void itoa2(int n, char s[]);
void reverse(char s[]);

main ()
{
	int n = -2147483648;
	char s1[MAXLINE], s2[MAXLINE];
	int i;

	for (i = 0; i < MAXLINE; i++)
		s1[i] = 0, s2[i] = 0;

	itoa(n, s1);
	itoa2(n, s2);
	printf("n: %d, s1: %s, s2: %s\n", n, s1, s2);
	printf("-n = %d, -n modulo 10 = %d, -n module 10 + '0' = %c\n", -n, (-n % 10), (-n % 10) + '0');
}

void reverse(char s[])
{
	int c, i, j;

	for (i = 0, j  = strlen(s)-1; i < j; i++, j--)
		c = s[i], s[i] = s[j], s[j] = c;
}

void itoa(int n, char s[])
{
	int i, sign;

	if ((sign = n) < 0)
		n = -n;
	i = 0;
	do {
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';
	reverse(s);
}

void itoa2(int n, char s[])
{
	int i, sign;
	int offset = 0;
	
	if ((sign = n) < 0) {
		n = -n;
		if (n < 0)
			n += 1, n = -n, offset = 1;
	}
	i = 0;
	do {
		s[i] = n % 10 + '0';
		if (i == 0)
			s[i] += offset;
		++i;
	} while ((n /= 10) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	reverse(s);
}
