#include<stdio.h>

/* write a loop equivalent to the for loop
 *
 * for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
 * 	s[i] = c;
 *
 * without using && or ||. */

#define	MAXLINE	100

main ()
{
	/* initializer */
	int i;
	int lim = MAXLINE;
	int c;
	char s[MAXLINE];

	for (i=0; i < lim-1; ++i) {
		if ((c=getchar()) != '\n')
			if (c != EOF)
				s[i] = c;
	}

	printf("%s\n", s);
}
