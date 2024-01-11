/* Write a program that will print arbitrary input in a sensible way. As a minimum, it should print non-graphic characters in octal or hexadecimal according to local custom, and break long text lines. */

/* discussion:
 * - how do we simulate arbitrary input?
 * 		generate a random stream of octals?
 * - how do we determine if such generated octals are non-graphic characters?
 * 		what's the range of ascii characters? how about unicode??
 * - can this be done using getchar, putchar?
 * 		what if my input is ^C (closing the program), ^D (EOF)? a terminal console running the program will just close it.
 * - how can i simulate an unborken long text line?
 * 		the console that's running the code will cast line-wrapping automatically. maybe in some low-level embedded system will require extra code, but not on my laptop.
 *
 * 	conclusion:
 * 		will resume to the exercise when the environment makes more sense to the problem. */

#include "template_clock.c"

#include <stdio.h>

int is_char(int);

int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	int i;
	/* 32 ~ 126 */
	for (i = 0; i < 256; i++) {
		if (is_char(i))
			printf("%10d\t%c\n", i, i);
		else
			printf("%10d\t%2.2X\n", i, i);
	}

	printf("\\n: %d\n", '\n');
	printf("EOF: %d\n", EOF);

	printf("\nprovide input:\n");

	int c;
	while ((c = getchar()) != EOF)
		putchar(c);






	time_measure_end();		/* code end */
	return 0;
}

int is_char(int n)
{
	int m = n % 256;
	if (32 <= m && m <= 126)
		return 1;
	return 0;
}
