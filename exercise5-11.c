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

#define TABSTEP	8
#define	MAXLEN	1000	/* maximum character input size */

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
	detab(s, t, tabstop);
	printf("%s\n%s\n", coln, s);
}

/* settabstop: takes arguments as tab stops, otherwise setting to the default TABSTEP */
void settabstop(int argc, char *argv[], int *tabstop)
{
	argv++;
	if (argc > 1)
		while (--argc > 0) {
			if (atoi(*(argv - 1)) < atoi(*argv))
				*tabstop++ = atoi(*argv);
			argv++;
		}
	else
		*tabstop++ = (TABSTEP != 0) ? TABSTEP : 8;
	*tabstop = 0;
}

/* detab: replaces tabs in the input with the proper number of blanks to space to the next tab stop. */
/* Example:
 * TABSTEP: 5
 * \tab\tcd e\tf
 * 01234567890123456789
 *      ab   cd e f */
void detab(char *output, char *input, int *tabstop)
{
	int p = 0;	/* current output position */
	int q = 0;	/* next tab stop position */
	int sp = 0;	/* spaces */

	printf("(detab) initial tabstop: %d\n", *tabstop);
	while (*input++ != '\0' && p <= MAXLEN) {
		/* update the next tab stop position */
		while (p + sp >= q)
			q = (*tabstop != 0) ? *tabstop++ : q + *(tabstop - 1);
		if (*(input-1) == ' ')
			sp += 1;
		else if (*(input-1) == '\t')
			sp += q - p;
		else {
			printf("(detab) p: %d, sp: %d, q: %d, c: '%c'\n", p, sp, q, *(input-1));
			if (sp > 0) {
				/* process space & tab here */
				while (sp-- > 0) {
					*output++ = ' ';
					p++;
				}
				if (++sp != 0)
					printf("(detab) error: %d spaces remaining after processing!\n", sp);
			}
			*output++ = *(input - 1);
			p++;
		}
	}
	*output = '\0';
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
