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
	 * in the problem, it states "Don't forget to handle quoted strings and character constants properly."
	 * a */
	printf("comment blocks can be expressed in strings like /* */\n");
}

void initialize(char s[], int maxline) {
	int i;

	for (i=0; i<maxline; ++i)
		s[i] = '\0';
}
