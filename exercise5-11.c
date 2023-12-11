/* Modify the program entab and detab to accept a list of tab stops as arguments. Use the default tab settings if there are no arguments. */

/* Added note
 * a list of tab stops
 * example: tabstop list: 2 6 15
 * ..2...6........15
 *   Foo Longname Bar
 *   0   1        2
 *   1   4        3
 *   2   8        0
 *   */

/* workflow
 * receives an input line
 * */

#include <stdio.h>
#include "getline.c"
#include "atoi.c"

#define TABSTEP	5
#define	MAXLEN	10	/* maximum character input size */

void settabstop(int argc, char *argv[], int *tabstop);
void detab(char *output, char *input, int *tabstop);
void entab(char *output, char *input, int *tabstop);

main(int argc, char *argv[])
{
	char coln[] = "012345678901234567890123456789";
	int tabstop[MAXLEN];
	settabstop(argc, argv, tabstop);

	char s[MAXLEN], t[MAXLEN];
	printf("current TABSTEP: %d\n", TABSTEP);
	printf("%s\n", coln);
	getline2(t, MAXLEN);
	entab(s, t, tabstop);
	printf("%s\n%s\n", coln, s);
}

void settabstop(int argc, char *argv[], int *tabstop)
{
	printf("(settabstop) tab stops: ");
	argv++;
	if (argc > 1)
		while (--argc > 0) {
			if (atoi(*(argv - 1)) < atoi(*argv)) {
				*tabstop++ = atoi(*argv);
				printf("%d ", *(tabstop - 1));
			}
			argv++;
		}
	else {
		*tabstop++ = (TABSTEP != 0) ? TABSTEP : 8;
		printf("%d ", *(tabstop - 1));
	}
	*tabstop = 0;
	printf("%d\n", *tabstop);
}

/* detab: replaces tabs in the input with the proper number of blanks to space to the next tab stop. */
/* Example:
 * TABSTEP: 5
 * \tab\tcd e\tf
 * 01234567890123456789
 *      ab   cd e f */
void detab(char *output, char *input, int *tabstop)
{
}

/* entab: replace strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. */
/* Example:
 * TABSTEP: 5
 * ab      cd  ef         g
 * 012345678901234567890123456789
 * ab\t ...cd..ef\t    ...g       */
/* Example (exercise 5-11 update)
 * TABSTEP: 5
 * entab 4 9 15
 * a..\t b...\t  cd......e
 * 012345678901234567890123456789
 * a\t ..b\t.....cd\t  ..e        */
void entab(char *output, char *input, int *tabstop)
{
}
