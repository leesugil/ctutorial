/* Write a program that convers upper case to lower or lower case to upper, depending on the name it is invoked with, as found in argv[0]. */

#include "template_clock.c"

#include <stdio.h>
#include <ctype.h>
#include <string.h>

static struct {
	unsigned int is_lower : 1;
	unsigned int is_upper : 1;
} flags;

int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	/* flag lower or upper */
	while (--argc > 0) {
		flags.is_lower = (strcmp(*++argv, "lower") == 0) ? 1 : 0;
		flags.is_upper = (strcmp(*argv, "upper") == 0) ? 1 : 0;
	}

	int c;
	while ((c = getchar()) != EOF) {
		if (flags.is_lower == 1)
			putchar(tolower(c));
		else if (flags.is_upper == 1)
			putchar(toupper(c));
		else
			putchar(c);
	}







	time_measure_end();		/* code end */
	return 0;
}

