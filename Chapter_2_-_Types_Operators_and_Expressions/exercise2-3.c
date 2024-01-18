#include <stdio.h>

/* Write a function which converts a string of hexadecimal digits (including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0 through 0, a through f, and A through F. */

#define	MAXLINE	100

void getline(char s[]);
void lower(char s[]);
int htoi(char s[]);

main ()
{
	char s[MAXLINE];
	int i;

	getline(s);
	lower(s);
	i = htoi(s);
	printf("hex input: %s\nint: %d\n", s, i);
}

void getline(char s[]) {
	int i;
	char c;
	for (i=0; i < MAXLINE-1 && (c=getchar()) != '\n' && c != EOF; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
}

void lower(char s[]) {
	int i;

	for (i=0; s[i] != '\0'; ++i)
		if ('A' <= s[i] && s[i] <= 'Z')
			s[i] = s[i] - ('A' - 'a');
}

int htoi(char s[]) {
	int i, j, k, m, n;
	char msg[] = "Something is wrong with the hexadecimal string format.\n";
	m = 0;
	n = 0;
	j = 0;
	k = 0;

	/* detect 0x first */
	for (i=0; s[i] != '\0' && s[i] != '\n'; ++i) {
		printf("s[i] = %c, m = %d\n", s[i], m);
		++m;
	}

	if (s[0] == '0') {
		if (m > 1) {
			if (s[1] == 'x') {
				j = 2;
			}
			else {
				printf("1%s\nm=%d\n", msg, m);
			}
		}
		else {
			printf("2%s\nThe only valid input hex in this case should be 0.\n", msg);
		}
	}

	for (i=j; i < m; ++i) {
		if ('0' <= s[i] && s[i] <= '9') {
			k = s[i] - '0';
		}
		else if ('a' <= s[i] && s[i] <= 'f') {
			k = 10 + (s[i] - 'a');
		}
		else {
			k = 0;
			printf("3%s\n", msg);
		}
		n = n*16 + k;
	}

	return n;
}

