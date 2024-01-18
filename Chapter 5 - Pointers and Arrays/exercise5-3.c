#include <stdio.h>

/* Write a pointer version of the function strcat that we showed in Chapter 2: strcat(s, t) copies the string t to the end of s */

/* this example assumes that s has enough space to store t at the end */

void strcat2(char *s, char *t)
{
	while (*s++)
		;
	--s;
	while ((*s++ = *t++))
		;
}

main()
{
	char s[65535] = "this is a pointer to a string constant.";
	char *t = "this is a pointer to another string constant to be concatenated to s.";
	
	strcat2(s, t);
	printf("%s\n", s);
}
