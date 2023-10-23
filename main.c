#include <stdio.h>
#define	MAXLINE	1000 /* maximum inputline length */

char pattern[] = "ould"; /* pattern to search for */

/* find all lines matching pattern */
main ()
{
	char line[MAXLINE];
	int found = 0;

	while (getline(line, MAXLINE) > 0)
		if (strindex(line, pattern) >= 0) {
			printf("%s", line);
			found++;
		}
	return found;
}
