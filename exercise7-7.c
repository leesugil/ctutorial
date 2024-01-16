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
	char keyword[MAXLINE];

	while (--argc > 0 && (*++argv)[0] == '-')
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
						fprintf(stderr, "find: illegal option %c\n", c);
						argc = 0;
						found = -1;
						break;
				}
	
	if (argc == 0 || (flags.file == 1 && argc < 2))
		printf("Usage: find -xnf pattern filename1 filename2 ...\n");
	else {
		strcpy(keyword, *argv);
		if (flags.file != 1) {	/* original code */
			while (getline(&line, &mline, stdin) > 0) {
				lineno++;
				if ((strstr(line, keyword) != NULL) != flags.except) {
					if (flags.number)
						printf("%ld:", lineno);
					printf("%s", line);
					found++;
				}
			}
		}
		else {
			/* *argv still indicating the pattern name */
			while (--argc > 0) {
				/* read file */
				if ((fp = fopen(*++argv, "r")) == NULL) {
					fprintf(stderr, "%s: can't open %s\n", prog, *argv);
					exit(1);
				} else {
					/* read lines from the file */
					char line2[MAXLINE];
					while (fgets(line2, MAXLINE-1, fp) != NULL) {
						lineno++;
						if ((strstr(line2, keyword) != NULL) != flags.except) {
							if (flags.number)
								printf("%ld:", lineno);
							printf("%s", line2);
							found++;
						}
					}
				}
			}
		}
	}
	return found;
}
