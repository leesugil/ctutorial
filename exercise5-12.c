/* Extend entab and detab to accept the shorthand
 * entab -m +n
 * to mean tab stops every n columns, starting at column m. Choose convenient (for the user) default behavior. */

#include <stdio.h>
#include "getline.c"
#include "atoi.c"

#define	MAXLEN	1000	/* maximum character input size */

void settabstop(int argc, char *argv[], int *tabstop);
void detab(char *output, char *input, int *tabstop);
void entab(char *output, char *input, int *tabstop);

int tabstep = 8;

main(int argc, char *argv[])
{
	char coln[] = "012345678901234567890123456789";
	int tabstop[MAXLEN];
	settabstop(argc, argv, tabstop);
	printf("tab stops: ");
	int i;
	for (i = 0; tabstop[i] != 0; i++)
		printf("%d ", tabstop[i]);
	printf("%d\n", tabstop[i]);

	char s[MAXLEN], t[MAXLEN];
	printf("current tabstep: %d\n", tabstep);
	printf("%s\n", coln);
	getline2(t, MAXLEN);
	detab(s, t, tabstop);
	printf("%s\n%s\n", coln, s);
}

/* settabstop: takes arguments as tab stops, otherwise setting to the default tabstep */
void settabstop(int argc, char *argv[], int *tabstop)
{
	argv++;
	char c;
	if (argc > 1) {
		/* more if-conditions for detecting -m +n pattern */
		if ((c = (*argv)[0]) == '-' || c == '+') {
			/* treat the -m +n pattern.
			 * update tabstep with n */
			if (c == '-') {
				printf("(settabstop) '-' detected\n");
				*tabstop++ = -1 * atoi((*argv++));
				c = (*argv)[0];
			}
			if (c == '+') {
				printf("(settabstop) '+' detected\n");
				tabstep = atoi(*argv++);
			}
		}
		else {
			/* treat the original pattern */
			while (--argc > 0) {
				if (atoi(*(argv - 1)) < atoi(*argv))
					*tabstop++ = atoi(*argv);
				argv++;
			}
		}
	}
	else {
		*tabstop++ = (tabstep != 0) ? tabstep : 8;
	}
	*tabstop = 0;
}

/* detab: replaces tabs in the input with the proper number of blanks to space to the next tab stop. */
void detab(char *output, char *input, int *tabstop)
{
	int p = 0;	/* current output position */
	int q = 0;	/* next tab stop position */
	int sp = 0;	/* spaces */

	while (*input++ != '\0' && p <= MAXLEN) {
		/* update the next tab stop position */
		while (p + sp >= q)
			q = (*tabstop != 0) ? *tabstop++ : q + tabstep;
		if (*(input-1) == ' ')
			sp += 1;
		else if (*(input-1) == '\t')
			sp += q - p;
		else {
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
void entab(char *output, char *input, int *tabstop)
{
	int *q = tabstop;	/* tab stops when analyzing input */
	int *r = tabstop;	/* tab stops when recording into output */
	int p = 0;	/* position index to compare with *q, *r */
	int sp = 0;	/* for p + sp */
	char c;
	char *input2 = output;	/* when spaces are replaced with tabs in output, we use detab to apply the tab stops using spaces given by detab */

	while ((c = *input++) != '\0' && p < MAXLEN) {
		/* update q */
		if (p + sp >= *q) {	/* (1) */
			if (*(q+1))
				q += 1;
			else
				*q += tabstep;
		}
		/* update r */
		if (p >= *r) {	/* (2) */
			if (*(r+1))
				r += 1;
			else
				*r += tabstep;
		}
		/* add spaces with q */
		if (c == ' ')
			sp++;
		else if (c == '\t') {
			sp += *q - (p + sp);	/* by (1) and this, *q > p + sp always */
		}
		else {
			/* c == char or '\n' */
			/* record c in p */
			if (sp > 0) {
				/* process spaces with r */
				while (p + sp >= *r) {
					*output++ = '\t';
					sp -= *r - p;
					p = *r;
					if (*(r+1))
						r++;
					else
						*r += tabstep;
				}
				while (sp-- > 0) {
					*output++ = ' ';
					p++;
				}
				if (!(sp + 1)) {
					sp = 0;
				}
				else
					printf("(entab) error, sp: %d is not balanced out at position p: %d.\n", sp, p);
			}
			*output++ = c;
			p++;
		}
	}
	*output = '\0';

	char tmp[MAXLEN];
	int i;
	for (i = 0; input2[i] != '\0'; i++)
		tmp[i] = input2[i];
	tmp[i] = '\0';
	detab(output, tmp, tabstop);
}
