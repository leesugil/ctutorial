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

	initialize(line, MAXLINE);
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
	/* read a line, distingush word blocks as blanks followed by non-blanks.
	 * this could be one of the following forms:
	 * 1) blank-word
	 * 2) blank-\n (special case)
	 * 2) blank-\0 (special case)
	 * for each i, when line[i] detects a blank, it could mean
	 * 1) the blank is continued from the previous blank
	 * 2) the blank indicates the end of a blank-non_blank  sequence and is the beginning of a new word block.
	 * therefore it is important to check the previous character line[i-1].
	 * however, if the blank is from line[0], there is no previous character.
	 * thus maybe we can define a in-word-blank status variable and start with in_word_blank_status = ON.
	 * in_word_blank_status = OFF if line[i] starts to become non-blank
	 * so the logic is,
	 * 1) at i, line[i] yields blank-word -> word[j] = \0, calculate length and print word[] accordingly. (re)set j, length, accordingly.
	 * 2) at i, line[i] yields blank-\n -> \n-blank-\n? because even if word-blank-\n within MAXCOL, it's still not the desired output based on the requirement that each line should end with the last non-blank character. the requirement inherently prevents any output in this case, it should be okay to just print \n-blank-\n. word[j] = \n, word[j+1] = \0, reset j, length.
	 * 3) at i, line[i] yields \0 -> word[j] = \0, calculate length and print word[] accordingly. ((re)set j, length, accordingly.) */
	
	int i, j, length;
	int in_word_blank, print_status, read_status;

	j = 0;
	length = 0;
	in_word_blank = ON;
	print_status = OFF;
	read_status = ON;

	for (i=0; i<MAXLINE; ++i) {
		if (line[i] == '\0') {
			/* end of line */
			print_status = ON;
			if (read_status == ON) {
				read_status = OFF;
			}
		}
		else if (line[i] == '\n') {
			/* line break */
			print_status = ON;
			/* this algorithm doesn't discreminate blank-word and blank-\n. later, word[0] = line[i] = \n will be registered which in turn not properly counting \n-word-type word length. here in this practice, bash prevents \n-word-type input anyway, so we ignore this issue and move on. */
		}
		else if (line[i] == ' ' || line[i] == '\t') {
			/* blank */
			if (in_word_blank == OFF) {
				print_status = ON;
			}
		}
		else {
			/* non-blank character */
			if (in_word_blank == ON) {
				in_word_blank = OFF;
			}
		}

		if (print_status == ON) {
			/* length calculation and print */
			word[j] = '\0';
			if (length + j > maxcol) {
				printf("\n");
				length = 0;
			}
			printf("%s", word);
			length = length + j;
			j = 0;
			initialize(word, MAXLINE);
			in_word_blank = ON;
			print_status = OFF;
		}

		if (read_status == ON) {
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
