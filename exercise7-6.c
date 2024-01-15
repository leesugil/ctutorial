/* Write a program to compare two files, printing the first line where they differ. */

#include <stdlib.h>
#include "template_clock.c"

#include <stdio.h>

int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	/* read two files as strings */
	FILE *fp;
	int maxlen = 100;
	char s1[maxlen], s2[maxlen];
	char f1[] = "file1", f2[] = "file2";

	fp = fopen(f1, "r");
	fgets(s1, maxlen+1, fp);
	fp = fopen(f2, "r");
	fgets(s2, maxlen+1, fp);
	fclose(fp);

	printf("file1: %s\n", s1);
	printf("file2: %s\n", s2);






	time_measure_end();		/* code end */
	exit(0);
}

