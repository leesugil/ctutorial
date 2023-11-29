#include <stdio.h>

main ()
{
	int x = 1, y = 2, z[10];
	int *ip;
	printf("x = %d, y = %d, z[0] = %d\n\t*ip = %d\n", x, y, z[0], *ip);
	ip = &x;
	printf("x = %d, y = %d, z[0] = %d\n\t*ip = %d\n", x, y, z[0], *ip);
	y = *ip;
	printf("x = %d, y = %d, z[0] = %d\n\t*ip = %d\n", x, y, z[0], *ip);
	*ip = 0;
	printf("x = %d, y = %d, z[0] = %d\n\t*ip = %d\n", x, y, z[0], *ip);
	ip = &z[0];
	printf("x = %d, y = %d, z[0] = %d\n\t*ip = %d\n", x, y, z[0], *ip);
}
