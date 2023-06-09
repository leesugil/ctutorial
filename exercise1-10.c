#include <stdio.h>

/* copy its input to output, replace each tab by \t and, each backspace by \b, and each backsplash by \\.*/
main()
{
	int c;

	while ((c = getchar()) != EOF) {
		if (c == '\t')
			printf("\\t");
		else if (c == '\b')
			printf("\\b");
		else if (c == '\\')
			printf("\\\\");
		else
			putchar(c);
	}
}
