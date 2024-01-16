/* Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are named as arguments, from the standard input. Should the file name be printed when a matching line is found? */

#include <stdio.h>
#include <string.h>
#include "getline.c"

#define MAXLINE 1000

struct {
	unsigned int except : 1;
	unsigned int number : 1;
} flags;

/* find: print lines that match pattern from 1st arg from files*/
int main(int argc, char *argv[])
{
	char line[MAXLINE];
	long lineno = 0;
	int c, found;

	while (--argc > 0 && (*++argv)[0] == '-')
		while ((c = *++argv[0]))
			switch (c) {
				case 'x':
					flags.except = 1;
					break;
				case 'n':
					flags.number = 1;
					break;
				default:
					printf("find: illegal option %c\n", c);
					argc = 0;
					found = -1;
					break;
			}
	
	if (argc != 1)
		printf("Usage: find -x -n pattern -f filename1 filename2 ...\n");
	else
		while (getline2(line, MAXLINE) > 0) {
			lineno++;
			if ((strstr(line, *argv) != NULL) != flags.except) {
				if (flags.number)
					printf("%ld:", lineno);
				printf("%s", line);
				found++;
			}
		}
	return found;
}
