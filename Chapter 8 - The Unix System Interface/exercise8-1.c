/* C template
 * Author: Sugil Steve Lee
 * Last Updated: 2024-01-14 */

/* Rewrite the program cat from Chapter 7 using read, write, open, and close instead of their standard library equivalents. Perform experiments to determine the relative speeds of the two versions. */

#include <stdlib.h>
#include "template_clock.c"

#include "syscalls.h"

/* cat */
int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	int fd, n;
	char *prog = argv[0];
	char buf[BUFSIZ];

	while (--argc > 0) {
		if ((fd = open(*++argv, O_RDONLY, 0)) == -1)
			fprintf(stderr, "%s: can't open %s\n", prog, *argv);
		else {
			/* read all lines */
			/* write to stdout */
			while ((n = read(fd, buf, BUFSIZ)) > 0) {
				write(1, buf, n);
			}
			/* close connection */
			close(fd);
		}
	}








	time_measure_end();		/* code end */
	exit(0);
}

