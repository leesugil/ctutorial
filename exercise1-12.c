#include <stdio.h>

#define	IN	0
#define	OUT	1
#define	TRUE	1
#define	FALSE	0

/* count lines, words, and characters in input
 * and prints its input one word per line */
main()
{
	int c, nl, nw, nc, state, pstate;

	state = OUT;
	pstate = FALSE;
	nl = nw = nc = 0;
	/* how do i know if the first character is not a blank? no. you need to count the OUT -> IN moments only. */
	while ((c = getchar()) != EOF) {
		++nc;
		if (c == '\n')
			++nl;
		if (c == ' ' || c == '\n' || c == '\t') {
			state = OUT;
			if (pstate == TRUE)
				printf("\n");
			pstate = FALSE;
		}
		else {
			if (state == OUT) {
				state = IN;
				++nw;
				pstate = TRUE;
			}
		}
		if (pstate == TRUE)
			putchar(c);
	}
	printf("%d %d %d\n", nl, nw, nc);
}
