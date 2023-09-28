#include <stdio.h>
#include <string.h>

#define	MAXLINE	1000

/* itoa: convert n to characters in s */
void itoa(int n, char s[]);
void reverse(char s[]);

main ()
{
	int n = -123;
	char s[MAXLINE];
	int i;

	for (i = 0; i < MAXLINE; i++)
		s[i] = 0;

	itoa(n, s);
	printf("n: %d, s: %s\n", n, s);
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
