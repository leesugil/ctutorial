#include <stdio.h>

/* Write the function any(s1, s2), which returns the first location in a string s1 where any character from the string s2 occurs, or -1 if s1 contains no characters from s2. (The standard library function strbrk does the same job but returns a pointer to the location. */

#define	MAXLINE	1000

enum {OFF, ON};

void get_line(char s[]);
void remove_char(char s[], int c);
int any(char s[], int c);

main ()
{
	char s1[MAXLINE], s2[MAXLINE];
	int i, j, k;
	j = -1;

	printf("s1:\n");
	get_line(s1);
	printf("\ns2:\n");
	get_line(s2);
	printf("\n");

	printf("Original s1: %s\n", s1);
	printf("Original s2: %s\n", s2);

	for (i=0; (s2[i] != '\0') && (s2[i] != '\n'); ++i) {
		k = any(s1, s2[i]);
		if (k > -1) {
			if (j < 0) {
				j = k;
			}
			else if (k < j) {
				j = k;
			}
		}
		printf("The current character to search is \"%c\", and its location in s1 is %d. The lowest number so far is %d.\n", s2[i], k, j);
	}

	printf("The first position that any character from s2 appears in s1: %d\n", j);
}

void get_line(char s[]) {
	int i, c;

	for (i=0; i < MAXLINE-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
}

void remove_char(char s[], int c) {
	int i, j;

	for (i=j=0; s[i] != '\0'; ++i) {
		if (s[i] != c) {
			s[j++] = s[i];
		}
	}
	s[j] = '\0';
}

int any(char s[], int c) {
	int i, j, status;
	j = -1;
	status = ON;

	for (i=0; i < MAXLINE-1 && s[i] != '\0' && status == ON; ++i) {
		if (s[i] == c) {
			j = i;
			status = OFF;
			printf("From the string\n%s, the letter \"%c\" was detected in the %d-th position.\n", s, c, j);
		}
	}

	return j;
}
