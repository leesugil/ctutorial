/* *++argv[1] vs. (*++argv)[1] */

#include <stdio.h>

main(int argc, char *argv[])
{
	printf("(*++argv)[2]: %c\n", (*++argv)[2]);
	--argv;
	printf("*++argv[2]: %c\n", *++argv[2]);
}
