#include <stdio.h>

#define	MAX	100
#define	IN	1	/* inside a word */
#define	OUT	0	/* outside a word */

/* histogram of the lengths of words in its input */
main()
{
	int c, i, j, l, state, cap;
	int freq[MAX];

	/* initialization */
	l = 0;
	cap = 0;
	state = OUT;
	for (i = 0; i < MAX; ++i)
		freq[i] = 0;

	while ((c = getchar()) != EOF) {
		/* a loop words */
		if (c == ' ' || c == '\n' || c == '\t') {
			if (state == IN) {
				/* IN -> OUT */
				++freq[l];
				if (l > cap) {
					cap = l;
				}
			}
			state = OUT;
			++freq[0];
			l = 0;
		}
		else {
			++l;
			if (state == OUT) {
				state = IN;
			}
		}
	}

	for (i = 0; i < cap + 1; ++i) {
		printf("%d: ", i);
		printf("%d", freq[i]);
		for (j = 0; j < freq[i]; ++j) {
			printf("*");
		}
		printf("\n");
	}
}
