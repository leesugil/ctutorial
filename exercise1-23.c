#include <stdio.h>

/* removes C comments */

#define	MAXLINE	1000
#define	TRUE	1
#define	FALSE	0

int getline(char input[], int maxline);
void remove_comment(char output[], char input[]);
void initialize(char s[], int maxline);

main()
{
	int len, i;
	char input_line[MAXLINE];
	char output_line[MAXLINE];

	initialize(input_line, MAXLINE);
	initialize(output_line, MAXLINE);

	while((len = getline(input_line, MAXLINE)) > 0) {
		/* len = 0 happens iff getchar() == EOF at i = 0 */
		remove_comment(output_line, input_line);
		printf("%s", output_line);
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

void remove_comment(char output[], char input[])
{
	/* basically copying input to output,
	 * but stops copying between comment blocks.
	 * thus we need a in_comment status variable.
	 * in the problem, it states "Don't forget to handle quoted strings and character constants properly."
	 * thus we need a in_string status variable.
	 * when in_string == FALSE, in_comment = ON/OFF depending on the comment brackets. */
	
	int i, j, in_comment, in_string, escape_sequence_detected;
	int comment_start, comment_end;

	j = 0;
	in_comment = FALSE;
	in_string = FALSE;
	escape_sequence_detected = FALSE;

	comment_start = FALSE;
	comment_end = FALSE;

	for (i=0; i<MAXLINE; ++i) {

		/* add a code here that detects strings.
		 * once a string is detected by a double quote, do not mistakenly close it by false-detecting \" as the end of the string. */

		if (input[i] == '"') {
			if (in_string == FALSE) {
				in_string = TRUE;
			}
			else if (escape_sequence_detected = FALSE) {
				in_string = FALSE;
			}
		}

		if ((in_string == TRUE) && (input[i] == '\\')) {
			escape_sequence_detected = TRUE;
		}
		else {
			escape_sequence_detected = FALSE;
		}

		/* this code prints out the initial / when entering comment. need a two-char variable to eliminate / & * as a whole */
		if ((input[i] == '*') && (in_string == FALSE)) {
			if (comment_start == TRUE) {
				in_comment = TRUE;
				comment_start = FALSE;
			}
			else if (in_comment == TRUE) {
				comment_end = TRUE;
			}
		}

		if (in_comment == FALSE) {
			output[j] = input[i];
			j++;
		}

		if ((input[i] == '/') && (in_string == FALSE)) {
			if (comment_end == TRUE) {
				in_comment = FALSE;
				comment_end = FALSE;
			}
			else if (in_comment == FALSE) {
				comment_start = TRUE;
			}
		}
	}
}

void initialize(char s[], int maxline) {
	int i;

	for (i=0; i<maxline; ++i)
		s[i] = '\0';
}
