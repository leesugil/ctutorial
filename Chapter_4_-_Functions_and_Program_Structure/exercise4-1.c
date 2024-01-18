#include <stdio.h>
#define	MAXLINE	1000 /* maximum inputline length */

int strindex(char s[], char t[]);

char pattern[] = "ould"; /* pattern to search for */

/* find all lines matching pattern */
main ()
{
	char line[MAXLINE];
	int found = 0;
	int position = 0;

	while (getline(line, MAXLINE) > 0)
		if ((position=strindex(line, pattern)) >= 0) {
			printf("%s", line);
			printf("%d\n", position);
			found++;
		}
	return printf("%d\n", found);
}

/* strindex(s, t):it returns the position of the rightmost occurence of t in s, or -1 if there is none */
int strindex(char s[], char t[])
{
	int i, j, k;
	int output = -1;

	for (i = 0; s[i] != '\0'; i++)
	{
		for (j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			output = i;
	}
	return output;
}
