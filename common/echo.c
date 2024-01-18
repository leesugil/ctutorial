#include <stdio.h>

/* echo command-line arguments; 2nd version */
main(int argc, char *argv[])
{
	while (--argc > 0)
		printf((argc > 1) ? "%s " : "%s", *++argv);
	return 0;
}
