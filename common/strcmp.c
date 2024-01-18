#include "cap.c"

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
	int output;
	char u, v;

	for ( ; *s - *t == 0 || (fold && lower(*s) - lower(*t) == 0); s++, t++)
		if (*s == '\0')
			return 0;

	u = *s, v = *t;
	if (fold)
		u = lower(u), v = lower(v);
	output = (u - v) * (1 - 2 * reverse);
	return output;
}
