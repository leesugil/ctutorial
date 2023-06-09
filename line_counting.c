#include <stdio.h>

/* count lines in input */
main()
{
	int c, nl;

	nl = 0;
	while ((c = getchar()) != EOF)
		if (c == '\n')
			++nl;
	printf("%d\n", nl);

	/* string constant, character constant, and escape sequences */
	printf("More on string constants and character constants\n"
		"A thing like \"hello, world!\" is called a character string or a string constant.\n"
		"A thing like \'a\' is called a character constant.\n"
		"Note that there are escape sequences such as \'\\n\' for new line,"
		"\'\\t\' for a tab, or \'\\b\' for backspace when used in double quotes.\n"
		"These escape sequences in a single quote also can be a character constant.\n"
		"For example, \'\\n\' is integer 10 as the value representing the newline character.\n"
		"%d\n", '\n');
}
