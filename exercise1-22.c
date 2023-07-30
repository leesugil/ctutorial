#include <stdio.h>

/* fold */

#define	MAXCOL	10
#define	MAXLINE	1000
#define	INWORD	1
#define	OUTWORD	0
#define	ON	1
#define	OFF	0

int getline(char input[], int maxline);
void fold(char line[], char word[], int maxcol);
void initialize(char s[], int maxline);

main()
{
	int len, i;
	char line[MAXLINE];
	char word[MAXLINE];

	initialize(word, MAXLINE);

	while((len = getline(line, MAXLINE)) > 0) {
		/* len = 0 happens iff getchar() == EOF at i = 0 */
		fold(line, word, MAXCOL);
	}

	return 0;
}

int getline(char s[], int maxline)
{
	int c, i;

	for (i = 0; i < maxline - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

void fold(char line[], char word[], int maxcol)
{
	int i, j, length, status, print_status;

	j = 0;
	length = 0;
	status = OUTWORD;
	print_status = OFF;
	/* read a word as a word with status = INWORD
	 * read a space group as a word with status = OUTWORD
	 * treat \n independantly
	 */
	/* this code has two flaws
	 * 1) when line[i] == '\\0', the loop stops, and the last word is omitted from the outcome.
	 * 2) when a word is longer than maxcol, the word is omitted. */
	for (i = 0; line[i] != '\0'; ++i) {
		if (line[i] == '\n') {
			/* change of line and line length */
			status = OUTWORD;
			printf("%c", line[i]);
			j = 0;
			length = 0;
		}
		else {
			/* when word -> blank or blank -> word,
			 * set print_status = ON.
			 * otherwise OFF. */
			if (line[i] == ' ' || line[i] == '\t') {
				if (status == INWORD) {
					/* word -> blank */
					status = OUTWORD;
					print_status = ON;
				}
			}
			else {
				if (status == OUTWORD) {
					/* blank -> word */
					status = INWORD;
					print_status = ON;
				}
			}

			/* measure the length, print the word properly,
			 * change line,
			 * reset length and j to 0 */
			if (print_status == ON) {
				/* length of word = j */
				if (length + j > maxcol) {
					printf("\n");
					length = 0;
				}
				word[j] = '\0';
				printf("%s", word);
				length = length + j;
				j = 0;
				initialize(word, MAXLINE);
				print_status = OFF;
			}
			word[j] = line[i];
			++j;
		}
	}
}

void initialize(char s[], int maxline) {
	int i;

	for (i=0; i<maxline; ++i)
		s[i] = '\0';
}
