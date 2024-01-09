#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define	MAXLINE	1000

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

/* itoa2: upgrades itoa, checks malloc */
char *itoa2(int n)
{
	int i, sign, m, d = 1;
	char *p;

	if ((sign = n) < 0) {
		n = -n;
		d++;
	}
	for (m = n; m > 0; m /= 10)
		d++;
	p = (char *) malloc(d * sizeof(char));
	for (i = 0; n > 0; n /= 10, i++)
		*(p+i) = n % 10 + '0';
	if (sign < 0)
		*(p+(i++)) = '-';
	*(p+i) = '\0';
	reverse(p);

	return p;
}

/* itoa3: upgrades itoa2, array to array conversion. */
void itoa3(int *v[], char *w[], int length)
{
	int i;
	for (i = 0; i < length; i++) {
		printf("(itoa3) %d <= %d < %d, *v[%d]: %d at %p\n", 0, i, length, i, *v[i], v[i]);
		printf("\tv[%d]: %d at %p\n", i, *v[i], v[i]);
		int j;
		j = *v[i];
		printf("\tv[%d]: %d at %p\n", i, *v[i], v[i]);
		w[i] = itoa2(j);
		printf("\tv[%d]: %d at %p\n", i, *v[i], v[i]);
		printf("(itoa3) *v[%d]: %d, w[%d]: %s\n", i, *v[i], i, w[i]);
	}
}
