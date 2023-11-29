#include <ctype.h>
#include <stdio.h>
#include "./calc/getch.c"

#define SIZE	10

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;
	while (isspace(c = getch()))	/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		/* it is not a number */
		ungetch(c);
		printf("(getint) %c is not a number.\n", c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		c = getch();
	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	printf("(getint) *pn = %d\n", *pn);
	return c;
}

main()
{
	int n, array[SIZE], getint(int *);

	printf("array[SIZE] = ");
	for (n = 0; n < SIZE; n++)
		printf("%d, ", array[n]);
	printf("\n");

	for (n = 0; n < SIZE && getint(&array[n]) != EOF; n++)
		;
	/* if getint takes an integer argument, passing array[n] as an integer wouldn't make any change to it */
	for (n = 0; n < SIZE && array[n] != EOF; n++)
		printf("array[%d] = %d\n", n, array[n]);
}

/* this example is kind of out of context for me, so here's an analysis.
   array[SIZE] should be an array that stores are the numbers captured in each getch() run.
   each getint(&array[n]) sets *pn = array[n] which is initially a garbage value.
   each getint(&array[n]) runs getch() which runs getchar() from string.h.
   if a non-number is entered, getint(&array[n]) returns 0 which does nothing.
   n++
   new getint(&array[n]) runs.
   this time captures a number.
   then the value is stored in *pn which is array[n].
   so i get what they mean by passing by reference here.
   when getint(&array[n]) returned 0 with non-number input, what was stored in array[n] before n++?
   wait, is EOF 0?
   no, EOF == -1.
   not all array[n] is initialized to be zero, how was it treated?
   it doesn't seem to make sense as the following reason:
   if inputs are numbers and spaces, it works well.
   if an input is a character c, then it ungetch(c) and return 0 which leads to n++, so the current array[n] was left at the garbage value and we moved on. furthermore, c was ungetted, so the next loop calls the same c = getch() which creates a cyclic loop through n++ until n < SIZE.
*/
