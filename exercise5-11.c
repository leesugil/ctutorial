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

#define TABSTEP	3
#define	MAXLEN	1000	/* maximum character input size */

void settabstop(int argc, char *argv[], int *tabstop);
void entab(char *output, char *input, int *tabstop);
void detab(char *output, char *input, int *tabstop);

main(int argc, char *argv[])
{
	char coln[] = "123456789012345678901234567890";
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
	while (--argc > 0)
		*(tabstop++) = atoi(*++argv);
}

/* spaces -> tabs + blanks */
void entab(char *output, char *input, int *tabstop)
{
	int spaces = 0;
	while (*input++ != '\0') {
		if (*(input-1) == ' ') {
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
				while (spaces >= TABSTEP) {
					*output++ = '\t';
					spaces -= TABSTEP;
					printf("(entab) applied a tab, remaining spaces: %d\n", spaces);
				}
				while (spaces-- > 0) {
					*output++ = ' ';
					printf("(entab) applied a space, remaining spaces: %d\n", spaces);
				}
				spaces = 0;
			}
			*output++ = *(input-1);
			printf("(entab) registered a character '%c'\n", *(input-1));
		}
	}
}

/* tabs -> spaces */
void detab(char *output, char *input, int *tabstop)
{
}
