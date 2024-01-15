/* Write a program to compare two files, printing the first line where they differ. */

#include <stdlib.h>
#include "template_clock.c"

#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	/* read two files as strings */
	FILE *fp1, *fp2;
	int maxlen = 100;
	char s1[maxlen], s2[maxlen];
	char f1[] = "file1", f2[] = "file2";

	fp1 = fopen(f1, "r");
	fp2 = fopen(f2, "r");

	/* compare the two line by line */
	while (strcmp(fgets(s1, maxlen+1, fp1), fgets(s2, maxlen+1, fp2)) == 0) {
		fprintf(stderr, "%s: %s", f1, s1);
		fprintf(stderr, "%s: %s", f2, s2);
	}

	/* display the first different line */
	printf("%s: %s", f1, s1);
	printf("%s: %s", f2, s2);

	/* close the program */
	fclose(fp1);
	fclose(fp2);






	time_measure_end();		/* code end */
	exit(0);
}

