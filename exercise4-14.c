#include <stdio.h>

/* Define a macto swap(y, x, y) that interchanges two arguments of type t. */

#define swap(t, x, y) {\
	t tmp;\
	tmp= x;\
	x = y;\
	y = tmp;\
}

main()
{
	double x, y;
	x = 1.0/7;
	y = 1.0/8;

	printf("x = %g, y = %g\n", x, y);
	swap(double, x, y);
	printf("swapped: x = %g,  y = %g\n", x, y);
}
