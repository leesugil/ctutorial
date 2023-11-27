#include <stdio.h>
#include <string.h>

/* Adapt the ideas of printd to write a recursive version of itoa; that is, convert an integer into a string by calling a recersive routine. */

#define	MAXLINE	1000

/* itoa: convert n to characters in s */
void itoa(int n, char s[]);
void reverse(char s[]);

main ()
{
	int n = -123023;
	char s[MAXLINE];
	int i;

	for (i = 0; i < MAXLINE; i++)
		s[i] = 0;

	itoa(n, s);
	printf("n: %d, s: %s\n", n, s);
}

void itoa(int n, char s[])
{
	static int p = 0;
	if (n < 0) {
		s[p++] = '-';
		n *= -1;
	}
	if (n / 10)
		itoa(n / 10, s);
	s[p++] = (n % 10) + '0';
}
