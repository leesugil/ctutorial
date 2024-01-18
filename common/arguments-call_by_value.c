#include <stdio.h>

int power(int base, int n);

main()
{
	printf("%d\n", power(-2, 9));
	return 0;
}

int power(int base, int n)
{
	int p;

	for (p = 1; n >0; --n)
		p = p * base;
	return p;
}
