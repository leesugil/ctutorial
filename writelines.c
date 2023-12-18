#include <stdio.h>

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	printf("(writelines) Printing output lines.\n");

	int i;

	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}
