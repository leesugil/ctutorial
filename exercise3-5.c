#include <stdio.h>
#include <string.h>

#define	MAXLINE	1000
#define	DEBUG	1

/* Write the function itob(n, s, b) that converts the integer n into a base b character representation in the string s. In particular, itob(n, s, 16) formats s as a hexadecimal integer in s. */

void itoa(int n, char s[]);
void itob(int n, char s[], int b);
void reverse(char s[]);

main ()
{
	int n = 256;
	int b = 16;
	char s[MAXLINE];
	int i;

	for (i = 0; i < MAXLINE; i++)
		s[i] = 0;

	itob(n, s, b);
	printf("n: %d, s: %s (%d)\n", n, s, b);
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
	int offset = 0; /* two's complement representation offset */
	
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

void itob(int n, char s[], int b)
{
	int i, sign;
	int offset = 0; /* two's complement representation offset */
	int m;
	
	if ((sign = n) < 0) {
		n = -n;
		if (n < 0)
			n += 1, n = -n, offset = 1;
	}
	i = 0;
	do {
		m = n % b;
		if (m > 9)
			m = m - 9 + 'a' - '1';
		s[i] = m + '0';
		if (i == 0)
			s[i] += offset;
		if (DEBUG)
			printf("i: %d, s[i]: %c, 's[i]': %d, n modulo b: %d\n", i, s[i], s[i], n % b);
		++i;
	} while ((n /= b) > 0);
	if (sign < 0)
		s[i++] = '-';
	s[i] = '\0';

	reverse(s);

}
