#include <stdio.h>

main()
{
	int n, a[5], *pa;

	pa = &a[0];

	for (n = 0; n < 5; n++)
		a[n] = n + 1;

	for (n = 0; n < 10; n++) {
		printf("array[%d] = %d\t address: %p\n", n, *(pa + n), pa + n);
	}
}
