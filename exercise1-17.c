#include <stdio.h>

#define MAX	1000	/* maximum number of characters in a line */
#define	MIN	5	/* print all input lines that are longer than MIN characters */

int getline(char line[], int min);

main()
{
	int i;
	int len;

	char line[MAX];
	char longline[MAX];

	i = 0;
	while ((len = getline(line, MAX)) > 0)
	{
		if (len > MIN)
			printf("%s", line);
	}

	return 0;
}

int getline(char line[], int min)
{
	int c, i;

	for (i = 0; i < MAX-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}
