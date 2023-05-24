#include <stdio.h>

/* count characters in input; 1st version */

/* okay, there's another annoying thing in this code.
 * neither my code or the copy-and-pasted code from the book works as i expect.
 * the problem is that the while loop doesn't seem to end,
 * so the function doesn't call the printf function.
 * why?
 * the same behavior was observed in the previous example,
 * that the while loop doesn't end at the end of the input stream but
 * getchar() stands by for waiting for the next input.
 * is there still a specific character that i could use as an EOF?
 * i don't get it, but i'm sure getchar() that i have works slightly
 * different from getchar() used in the book.
 */

main()
{
	long nc;

	nc = 0;
	while (getchar() != EOF)
		++nc;
	printf("%ld\n", nc);
}

