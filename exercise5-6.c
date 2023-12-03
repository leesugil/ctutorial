#include <stdio.h>
#include <ctype.h>
#include <string.h>

/* Rewrite appropriate programs from earlier chapters and exercises with pointers instead of array indexing. Good possibilities include getline, atoi, itoa, and their variants, reverse, and strindex and getop. */

#define MAXLINE 1000
#define NUMBER '0'

int getline2(char *s, int lim);
void getline2_test(char *s, int lim);
int atoi(char *s);
void atoi_test(char *s, int lim);
void itoa(int n, char *s);
void itoa_test(int n, char *s, int lim);
void reverse(char *s);
void reverse_test(char *s, int lim);
int strindex(char *s, char *t);
void strindex_test(char *s, char *t, int lim);
int getop(char *s);
void getop_test(char *s, int lim);

main()
{
	char s[MAXLINE], t[MAXLINE];
	int n;

	getline2_test(s, MAXLINE);
	atoi_test(s, MAXLINE);
	itoa_test(n, s, MAXLINE);
	reverse_test(s, MAXLINE);
	strindex_test(s, t, MAXLINE);
	getop_test(s, MAXLINE);
}

/* getline2: get line into s, return length.
 * 2 to avoid conflict. */
int getline2(char *s, int lim) {
	char *t = s;
	while (s < t + lim - 1 && (*s = getchar()) != EOF && *s++ != '\n')
		;
	if (*(s-1) == '\n')
		s--;
	*s = '\0';
	return s - t;
}

void getline2_test(char *s, int lim) {
	printf("testing getline2...\n");
	printf("...provide a string constant as an input: ");
	printf("...output: %d, %s\n", getline2(s, lim), s);
}

int atoi(char *s) {
	int sign, n = 0;
	while (isspace(*s++))
		;
	sign = (*--s == '-') ? -1 : 1;
	if (sign == -1)
		printf("sign is %d\n", sign);
	if (*s == '+' || *s == '-')
		s++;
	while (isdigit(*s))
		n = 10 * n + (*s++ - '0');
	return sign * n;
}

void atoi_test(char *s, int lim) {
	printf("\ntesting atoi...\n");
	printf("...provide an integer as an input: ");
	getline2(s, lim);
	printf("...output: %d, %s\n", atoi(s), s);
}

void itoa(int n, char *s) {
	/* place reverse(s) in a proper place */
	static int sign, p = 0;
	if (n < 0) {
		sign = -1;
		n *= sign;
	}
	*s = (n % 10) + '0';
	if (n / 10) {
		++p;
		itoa(n / 10, s + 1);
		--p;
	}
	else {
		if (sign < 0)
			*++s = '-';
		*++s = '\0';
	}
	if (!p) {
		printf("...itoa: s before reverse: %s\n", s);
		printf("...itoa: strlen(s): %lu\n", strlen(s));
		reverse(s);
		sign = 0;
		p = 0;
	}
}

void itoa_test(int n, char *s, int lim) {
	printf("\ntesting itoa...\n");
	printf("...provide an integer as an input: ");
	getline2(s, lim);
	printf("...the input integer is %d\n", n = atoi(s));
	itoa(n, s);
	printf("...output: %s, %d\n", s, n);
}

void reverse(char *s) {
	static int p = 0;
	int l = strlen(s);
	char c;

	printf("...reverse: s, p, l = %s, %d, %d\n", s, p, l);
	if (0 <= p && p < l/2) {
		c = *(s + p);
		*(s + p) = *(s + l - 1 - p);
		*(s + l - 1 - (p++)) = c;
		reverse(s);
	}
	else
		p = 0;
}

void reverse_test(char *s, int lim) {
	printf("\ntesting reverse...\n");
	printf("...provide a string constant as an input: ");
	getline2(s, lim);
	reverse(s);
	printf("...output: %s\n", s);
}

/* strindex: return index of t in s, -1 if none */
int strindex(char *s, char *t) {
	char *u, *v, *w;
	for (u = s; *s != '\0'; s++) {
		for (v = s, w = t; *w != '\0' && *v == *w; v++, w++)
			;
		if (*w == '\0') {
			printf("...strindex: returning s - u\n");
			return s - u;
		}
	}
	return -1;
}

void strindex_test(char *s, char *t, int lim) {
	int n;
	printf("\ntesting strindex...\n");
	printf("...provide a base string constant: ");
	getline2(s, lim);
	printf("...provide a reference string constant: ");
	getline2(t, lim);
	printf("...output: %d\n\t%s\n", n = strindex(s, t), s);
	printf("\t%*s%s\n", n, "", t);
}

int getop(char *s) {
	return 0;
}

void getop_test(char *s, int lim) {
	printf("\ntesting getop...\n");
	printf("...provide an input operator/operand: ");
	printf("\n...output: %d\n", getop(s));
}

