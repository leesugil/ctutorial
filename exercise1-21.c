#include <stdio.h>

#define	TABSTEP	6	/* minimum tab spacing size */
#define	MAXLEN	1000	/* maximum character input size */

int getline(char line[], int max);
void entab(char output[], char input[]);	/* spaces are turned to tabs */
void detab(char output[], char input[]);	/* tabs are turned to spaces */

main()
{
	int len;
	char line[MAXLEN];
	char line_entabbed[MAXLEN];
	char line_detabbed[MAXLEN];

	/* when getchar() is EOF, the while loop breaks */
	while ((len = getline(line, MAXLEN)) > 0) {
		/* entabbing here */
		entab(line_entabbed, line);
		/* detabbing here */
		detab(line_detabbed, line_entabbed);
		/* print out a detabbed line */
		printf("%s", line_detabbed);
	}
}

int getline(char line[], int max)
{
	/* takes one line only at a time
	 * (no matter how many lines a single input provides until EOF */
	int c, i;

	for (i = 0; i < max - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

void entab(char output[], char input[])
{
	int i, j;
	/* code here */
}

void detab(char output[], char input[])
{
	int i, j;

	j = 0;
	for (i = 0; input[i] != '\0'; ++i) {
		if (j < MAXLEN - 1) {
			if (input[i] == '\t') {
				/* detab here */
				output[j] = ' ';
				++j;
				while (j % TABSTEP != 0) {
					if (j < MAXLEN - 1) {
						output[j] = ' ';
						++j;
					}
				}
			}
			else {
				output[j] = input[i];
				++j;
			}
		}
	}
	output[j] = '\0';
}
