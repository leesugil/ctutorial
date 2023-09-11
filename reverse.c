#include <string.h>
#include <stdio.h>
#define	DEBUG	1

/* reverse: reverse string s in place */
void reverse(char s[]);

main()
{
	int n=10;
	char s[n];
	int i;

	for (i=0; i<n; i++) {
		s[i] = 'a' + ((i * 32 + 8) % ('Z' - 'a'));
	}

	printf("Original string:\n%s\n", s);
	reverse(s);
	printf("Reversed string:\n%s\n", s);
}

void reverse(char s[])
{
	int c, i, j;

	for (i=0, j=strlen(s)-1; i<j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}
