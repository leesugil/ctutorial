#include <stdio.h>
#include <string.h>

#define	MAXLINE	1000
#define	DEBUG	1

/* Write a version of itoa that accepts three arguments instead of two. The third argument is a minimum field width; the converted number must be padded with blanks on the left if necessary to make it wide enough. */

void itoa(int n, char s[]);
void itoa2(int n, char s[], int w);
void itob(int n, char s[], int b);
void itob2(int n, char s[], int b, int w);
void reverse(char s[]);

main ()
{
	int n = 256;
	char s[MAXLINE];
	int i;
	int w = 7;

	for (i = 0; i < MAXLINE; i++)
		s[i] = 0;
	itoa(n, s);
	printf("n: %d, s: %s\n", n, s);
	itoa2(n, s, w);
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
	itob(n, s, 10);
}

/* Exercise 3-6 */
void itoa2(int n, char s[], int w)
{
	itob2(n, s, 10, w);
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

void itob2(int n, char s[], int b, int w)
{
	itob(n, s, b);

	reverse(s);
	int g = w / strlen(s);
	if (DEBUG)
		printf("w: %d, strlen(s): %ld, g: %d\n", w, strlen(s), g);
	int i, j, k;
	char s2[MAXLINE];

	for (i = 0; i < strlen(s); i++)
		s2[i] = s[i];
	s2[i] = '\0';
	if (DEBUG)
		printf("s2: %s\n", s2);

	for (i = 0, j = 0; i < strlen(s2); i++, j++) {
		s[j] = s2[i];
		for (k = 0; k < g-1; k++) {
			j++;
			s[j] = '*';
		}
		if (DEBUG)
			printf("s: %s\n", s);
	}
	for (i = j; i < w; i++)
		s[i] = '*';
	s[i] = '\0';
	reverse(s);
}
