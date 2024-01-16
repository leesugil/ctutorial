/* Write a program to print a set of files, starting each new one on a new page, with a title and a running page count for each file. */

#include <stdlib.h>
#include "template_clock.c"

#include <stdio.h>
#include <string.h>

#define MAXLINE 50	/* number of lines per page */
#define MAXLEN 20	/* number of characters per line */

void update_no(int *, int *);

struct {
	unsigned int display_col : 1;
} flags;

int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	FILE *fp;
	int pageno = 0, lineno = 0;
	char *prog = argv[0];
	char line[MAXLEN+1];

	flags.display_col = 1;

	while (--argc > 0) {
		/* open a file */
		if ((fp = fopen(*++argv, "r")) == NULL)
			fprintf(stderr, "%s: can't open %s\n", prog, *argv);
		else {
			/* print title and page no */
			while (fgets(line, MAXLEN+1, fp) != NULL) {
				update_no(&pageno, &lineno);
				printf("%s", line);
				if (strlen(line) >= MAXLEN && line[MAXLEN-1] != '\n')
					printf("\n");
			}
		}
	}








	time_measure_end();		/* code end */
	exit(0);
}

void update_col(void);

void update_no(int *pageno, int *lineno)
{
	update_col();

	if ((*lineno)++ >= MAXLINE) {
		*lineno %= MAXLINE;
		(*pageno)++;
	}
	printf("%4d %3d: ", *pageno+1, *lineno);
}

void update_col(void)
{
	if (flags.display_col == 1) {
		int i, j, m = 10;

		for (i = 0; i < 10; i++)
			printf(" ");
		for (i = 0; i < MAXLEN/m; i++)
			printf("%10d", i+1);
		printf("\n");

		for (i = 0; i < 10; i++)
			printf(" ");
		for (i = 0; i < MAXLEN/m; i++)
			for (j = 1; j < m+1; j++)
				printf("%d", j % m);
		printf("\n");

		flags.display_col = 0;
	}
}
