#include <stdio.h>

/* Write versions of the library functions strcpy, strcat, and strcmp, which operate on at most the first n characters of their argument strings. For example, strcpy(s, t, n) copies at most n characters of t to s. */

void strncpy2(char *s, char *t, int n);
void strncat2(char *s, char *t, int n);
int strncmp2(char *s, char *t, int n);

main()
{
	char s[50] = "90's games rock! ";
	char t[50] = "90's games roll!";
	int n = 7;

	printf("1234567890\n%s\n%s\n", s, t);
	if (0) {
		strncpy2(s, t, n);
		printf("strncpy2: %s\n", t);
	}
	else if (0) {
		strncat2(s, t, n);
		printf("strncat2: %s\n", s);
	}
	else {
		printf("strncmp2: %d\n", strncmp2(s, t, n));
	}
}

void strncpy2(char *s, char *t, int n)
{
	/* assume t is longer than s,
	 * which its length is bigger than or equal to n.*/
	char *u = t;
	while (t < u + n && (*t++ = *s++))
		printf("%p, %c\n", t-1, *(t-1));
	if (*(t-1) != '\0')	/* cut off at n */
		*t = '\0';
}

void strncat2(char *s, char *t, int n)
{
	/* assume s is long enough to accomodate t */
	char *u;
	while (*s++)
		;
	u = --s;
	while (s < u + n && (*s++ = *t++))
		;
	if (*(s-1) != '\0')	/* cut off at n */
		*s = '\0';
}

int strncmp2(char *s, char *t, int n)
{
	char *u = s;
	for ( ; s < u + n && *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	printf("%c, %c\n", *s, *t);
	return *s - *t;
}
