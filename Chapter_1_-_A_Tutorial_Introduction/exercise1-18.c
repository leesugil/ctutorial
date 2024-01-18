#include <stdio.h>

#define MAX	1000	/* maximum number of characters in a line */
#define	MIN	5	/* print all input lines that are longer than MIN characters */

int getline(char line[], int min);

/* remove trailing blanks and tabs from each line of input, and delete entirely blank lines. */
main()
{
	int i;
	int len;

	char line[MAX];
	char longline[MAX];

	i = 0;
	while ((len = getline(line, MAX)) > 0)
	{
		if (len > 1)
			printf("%s", line);
	}

	return 0;
}

int getline(char line[], int min)
{
	int c, i, j;

	for (i = 0; i < MAX-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	printf("original line length including \\n: %d\n", i);

	/* the last character line[i] is always '\0'.
	 * the second last character is assumed to be '\n'.
	 * thus we check the third last character line[i-2] */
	for (j = i; j - 2 >= 0 && (line[j-2] == ' ' || line[j-2] == '\t'); --j) {
		line[j-2] = '\n';
		line[j-1] = '\0';
	}
	printf("revised line length including \\n: %d\n", j);

	return j;
}
