#include <stdio.h>
#include <string.h>

/* Write the function strend(s, t), which returns 1 if the string t occurs at the end of the string s, and zero otherwise. */

int strend2(char *s, char *t)
{
	int output = 0;
	char *u = t;
	if (strlen(t) <= strlen(s)) {
		s += strlen(s) - 1;
		t += strlen(t) - 1;
		while (*(s--) == *(t--)) {
			printf("%c, %c\n", *(s+1), *(t+1));
		}
		printf("%c, %c, %c\n", *(s+1), *(t+1), *u);
		printf("t+2: %p, u: %p\n", t+2, u);
		if ((t+2) == u)
			return 1;
		return 0;
	}
	else
		return 0;
}

main()
{
	char *s = "Hello, World!";
	char *t = "rld!";
	char *o = "Hello,";

	printf("strend2(s, t): %d\n", strend2(s, t));
	printf("strend2(s, o): %d\n", strend2(s, o));
}
