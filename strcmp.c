/* strcmp2: return <0 if s<t, 0 if s==t, >0 if s>t */
int strcmp2(char *s, char *t)
{
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	return *s - *t;
}

/* strcmp3: return <0 if s<t, 0 if s==t, >0 if s>t. accepts reverse, fold. */
int strcmp3(char *s, char *t, int reverse, int fold)
{
	/* reverse: 1 if reverse
	 * fold: 1 if fold */
	for ( ; *s == *t; s++, t++)
		if (*s == '\0')
			return 0;
	printf("(strcmp3) *s - *t: %d, *s - *t (reverse): %d\n", *s - *t, (*s - *t) * (1 - 2 * reverse));
	return (*s - *t) * (1 - 2 * reverse);
}
