#include <stdio.h>

/* reverses character string and line */

#define	MAX	1000	/* max number of characters in a line */

int getline(char line[], int max);
void reverse(char to[], char from[]);

main()
{
	int c, len;
	char line[MAX];
	char reversed[MAX];

	while ((c = getline(line, MAX)) > 0) {
		reverse(reversed, line);
		printf("%s", reversed);
	}

	return 0;
}

int getline(char line[], int max)
{
	int i, c;

	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; i++) {
		line[i] = c;
	}
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';

	return i;
}

void reverse(char to[], char from[])
{
	int i, m;

	/* note that the last two characters should be \n and \0, and only the remaining characters should be reversed. */
	for (m = 0; from[m] != '\0'; ++m)
		;
	
	for (i = 0; i < m - 1; ++i)
		to[i] = from[m - 2 - i];

	to[i] = from [m - 1];
	to[i + 1] = from[m];
}
