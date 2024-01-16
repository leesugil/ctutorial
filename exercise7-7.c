/* Modify the pattern finding program of Chapter 5 to take its input from a set of named files or, if no files are named as arguments, from the standard input. Should the file name be printed when a matching line is found? */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 1000

struct {
	unsigned int except : 1;
	unsigned int number : 1;
	unsigned int file : 1;
} flags;

/* find: print lines that match pattern from 1st arg from files*/
int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t mline = 0;
	long lineno = 0;
	int c, found;
	FILE *fp;
	char *prog = argv[0];

	while (--argc > 0) {
		if ((*++argv)[0] == '-' && flags.file != 1) {
			while ((c = *++argv[0]))
				switch (c) {
					case 'x':
						flags.except = 1;
						break;
					case 'n':
						flags.number = 1;
						break;
					case 'f':
						flags.file = 1;
						break;
					default:
						printf("find: illegal option %c\n", c);
						argc = 0;
						found = -1;
						break;
				}
		}
		else if (flags.file == 1) {
			/* open file and feed */
			if ((fp = fopen(*argv, "r")) == NULL) {
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
				exit(1);
			} else {
				/* feed */
				fclose(fp);
			}
		}
	}
	
	if (argc != 1)
		printf("Usage: find -x -n pattern -f filename1 filename2 ...\n");
	else
		while (getline(&line, &mline, stdin) > 0) {
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
