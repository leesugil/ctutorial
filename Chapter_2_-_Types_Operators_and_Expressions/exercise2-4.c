#include <stdio.h>

/* Write an alternative version of squeeze(s1, s2)
 * that deletes each character in s1
 * that matches any character in the string s2. */

#define	MAXLINE	1000

void get_line(char s[]);
void remove_char(char[], int c);

main ()
{
	char s1[MAXLINE], s2[MAXLINE];
	int i;

	printf("s1:\n");
	get_line(s1);
	printf("\ns2:\n");
	get_line(s2);
	printf("\n");

	printf("Original s1: %s\n", s1);
	printf("Original s2: %s\n", s2);

	for (i=0; (s2[i] != '\0') && (s2[i] != '\n'); ++i) {
		remove_char(s1, s2[i]);
		printf("Removed %c to yield s1: %s\n", s2[i], s1);
	}

	printf("Modified s1: %s\n", s1);
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
