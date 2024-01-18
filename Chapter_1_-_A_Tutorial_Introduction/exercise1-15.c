#include <stdio.h>

#define	LOWER	0
#define	UPPER	300
#define	STEP	20

float f_to_c(int m);

main()
{
	int i;

	for (i = LOWER; i < UPPER; i = i + STEP)
		printf("%d	%6.1f\n", i, f_to_c(i));
	return 0;
}

float f_to_c(int m) {
	return (5.0/9.0) * (m - 32.0);
}
