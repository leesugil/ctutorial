#include <stdio.h>

/* blank counter */
main()
{
	int c, nb;

	nb = 0;
	while ((c = getchar()) != EOF)
		if (c == ' ')
			nb++;
	printf("%d\n", nb);
}
