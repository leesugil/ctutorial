#include <stdio.h>

/* Write a function escapte(s, t) that convers characters like newline and tab into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write a function for the other directions as well, converting escape sequences into the real characters. */

#define	MAXLINE	1000
#define	DEBUG	0

void get_line(char s[]);
void escape(char s[], char t[]);
void escape_reverse(char s[], char t[]);

main ()
{
	int c, i, nwhite, nother, ndigit[10];
	char s[MAXLINE], t[MAXLINE];

	nwhite = nother = 0;
	for (i=0; i<MAXLINE; i++)
		s[i] = t[i] = 0;

	get_line(t);
	printf("initial input\ns: %s\nt: %s\n", s, t);

	escape(s, t); /* s <- t */
	printf("escape applied\nt: %s\n-> s: %s\n", t, s);
	
	for (i=0; i<MAXLINE; i++)
		t[i] = 0;

	escape_reverse(s, t); /* s -> t */
	printf("escape_reverse applied\ns: %s\n-> t: %s\n", s, t);
	
	return 0;
}

void get_line(char s[]) {
	int c, i;

	for (i=0; i<MAXLINE-1 && ((c=getchar()) != EOF); i++)
		s[i] = c;
	s[i] = '\0';
}

void escape(char s[], char t[]) {
	/* s <- t */
	int i, j;

	for (i=j=0; j<MAXLINE-1 && t[i] != '\0'; i++) {
		if (DEBUG)
			printf("i=%d, t[i]=%c, j=%d, s[j]=%c\n", i, t[i], j, s[j]);
		switch(t[i]) {
			case '\n':
				s[j++] = '\\';
				s[j++] = 'n';
				break;
			case '\t':
				s[j++] = '\\';
				s[j++] = 't';
				break;
			default:
				s[j++] = t[i];
				break;
		}
		if (DEBUG)
			printf("i=%d, t[i]=%c, j=%d, s[j]=%c\n", i, t[i], j, s[j]);
	}
	s[j] = '\0';
}

void escape_reverse(char s[], char t[]) {
	/* s -> t */
	int i, j;

	for (i=j=0; i<MAXLINE && s[i] != '\0'; i++) {
		if (DEBUG)
			printf("before the current loop:\ni=%d, s[i]=%c, j=%d, t[j]=%c\n", i, s[i], j, t[j]);
		if (s[i] == '\\') {
			switch(s[i+1]) {
				case 't': /* \t */
					t[j++] = '\t';
					++i;
					break;
				case 'n': /* \n */
					t[j++] = '\n';
					++i;
					break;
				default: /* // or the rest of cases */
					t[j++] = s[i];
					break;
			}
		}
		else
			t[j++] = s[i];
		if (DEBUG)
			printf("after the current loop:\ni=%d, s[i]=%c, j=%d, t[j]=%c\n", i, s[i], j, t[j]);
	}
	t[j] = '\0';
}

