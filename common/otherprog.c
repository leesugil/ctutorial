#include <stdio.h>

int main()
{
	char *s = NULL;
	size_t MAXLEN = 0;
	while (getline(&s, &MAXLEN, stdin) > 0)
		printf("(otherprog) %s", s);
}
