#include <stdio.h>
#include <string.h>

/* Write a recursive version of the function reverse(s), which reverses the string s in place. */

void reverse(char s[])
{
	static int p = 0;
	int l = strlen(s);
	int tmp;
	if (p < (l / 2)) {
		p++;
		reverse(s);
	}
	if (p >= 0) {
		tmp = s[p];
		s[p] = s[l-1-p];
		s[l-1-p] = tmp;
		p--;
		printf("p = %d, l = %d, s[p] = %c, s[l-p] = %c\n", p, l, s[p], s[l-p]);
		printf("\t%s\n", s);
	}
}

main()
{
	char s[] = "hej!?";
	printf("%s\n", s);
	reverse(s);
	printf("%s\n", s);
}
