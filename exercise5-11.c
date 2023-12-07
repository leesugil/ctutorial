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
	int tabstop[argc - 1];
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
	if (argc > 1)
		while (--argc > 0)
			*(tabstop++) = atoi(*++argv);
	else
		*tabstop++ = (TABSTEP != 0) ? TABSTEP : 7;
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
	int i, n, p = 0;	/* tracks current position count of the output */
	while (*input++ != '\0') {
		if (*(input-1) == '\t') {
			/* at the current position p, move to the neariest next tab stop */
			n = TABSTEP - (p % TABSTEP);
			printf("(detab) tab detected at position %d, spacing %d to the next tab stop.\n", p, n);
			for (i = 0; i < n; i++, p++)
				*output++ = ' ';
		}
		else {
			*output++ = *(input-1);
			p++;
		}
	}
}

/* entab: replace strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. */
/* Example:
 * TABSTEP: 5
 * ab      cd  ef         g
 * 012345678901234567890123456789
 * ab\t ...cd..ef\t    ...g       */
/* the code needs to be updated as each time tab is used, tab stops should be considered */
void entab(char *output, char *input, int *tabstop)
{
	int i, n, p = 0, spaces = 0;
	while (*input++ != '\0') {
		if (*(input-1) == ' ') {
			/* accuulate spaces */
			spaces++;
			printf("(entab) detected space. spaces: %d\n", spaces);
		}
		else if (*(input-1) == '\t') {
			printf("(entab) detected tab. spaces: %d\n", spaces);
			spaces += TABSTEP;
		}
		else {
			if (spaces > 0) {
				/* store the tabs and spaces to *output before storing the current *input to the *output */
				/* determing how many tabs to apply. */
				printf("(entab) processing %d spaces\n", spaces);
				n = TABSTEP - (p % TABSTEP);
				if (n <= spaces) {
					/* initial tab to the nearest next tab stop */
					*output++ = '\t';
					p += n;
					spaces -= n;
					printf("(entab) applied a tab, remaining spaces: %d, current position: %d\n", spaces, p);
				}
				while (spaces >= TABSTEP) {
					*output++ = '\t';
					p += TABSTEP;
					spaces -= TABSTEP;
					printf("(entab) applied a tab, remaining spaces: %d, current position: %d\n", spaces, p);
				}
				while (spaces-- > 0) {
					*output++ = ' ';
					p++;
					printf("(entab) applied a space, remaining spaces: %d, surrent position: %d\n", spaces, p);
				}
				spaces = 0;
			}
			*output++ = *(input-1);
			p++;
			printf("(entab) registered a character '%c' at position %d\n", *(input-1), p-1);
		}
	}
}
