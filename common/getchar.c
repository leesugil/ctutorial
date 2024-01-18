/* C template
 * Author: Sugil Steve Lee
 * Last Updated: 2024-01-14 */

#include <stdlib.h>
#include "template_clock.c"

#undef getchar

#include "syscalls.h"

int getchar(void);

/* getchar: simple buffered version */
int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	char c;

	while ((c = getchar()) > 0)
		printf("%c", c);







	time_measure_end();		/* code end */
	exit(0);
}

int getchar(void)
{
	static char buf[BUFSIZ];
	static char *bufp = buf;
	static int n = 0;

	if (n == 0) {
		n = read(0, buf, sizeof buf);
		bufp = buf;
	}
	return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}
