/* strcmp2: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp2(char *s, char *t)
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

/* strcmp3: return <0 if s<t, 0 if s==t, >0 if s>t. accepts reverse, fold. */
/* this has a serious error. maybe my rough guess was wrong with how the qsort algorithm was implemented. maybe i shouldn't just modulo 'a' - 'A' but maybe treat all 'A's as 'a's. */
int strcmp3(char *s, char *t, int reverse, int fold)
{
	/* reverse: 1 if reverse
	 * fold: 1 if fold */
	int c, output;

	for ( ; (c = *s - *t) == 0 || c == ('a' - 'A') * fold || c == ('A' - 'a') * fold; s++, t++) {
		printf("(strcmp3) comparing %c, %c\n", *s, *t);
		if (c == 'a' - 'A' || c == 'A' - 'a')
			printf("(strcmp3) %c == %c\n", *s, *t);
		if (*s == '\0') {
			printf("(strcmp3) match! returning 0\n");
			return 0;
		}
	}
	printf("(strcmp3) mismatch! diff: %c, %c\n", *s, *t);

	output = (*s - *t) * (1 - 2 * reverse);
	printf("(strcmp3) returning %d\n", output);
	return output;
}
