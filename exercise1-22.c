#include <stdio.h>

/* fold */

#define	MAXCOL	10
#define	MAXLINE	1000

int getline(char input[], int maxline);
void fold(char output[], char input[]);

main()
{
	int c, i, max, len;
	char input[MAXLINE];
	char output[2 * MAXLINE];

	while((len = getline(input, MAXLINE)) > 0) {
		fold(output, input);
	}
}

int getline(char s[], int maxline)
{
	int c, i;

	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void fold(char out[], char in[])
{
	printf("%s", in);
}
