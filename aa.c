/* ASCII ART */

/* matsuri fan man */

char *art[] = {
	"   _   ",
	" ('v') ",
	"//-=-\\\\",
	"(\\_=_/)",
	" ^^ ^^ ",
};

/* C template
 * Author: Sugil Steve Lee
 * Last Updated: 2024-01-14 */

#include <stdlib.h>
#include "template_clock.c"

#include <unistd.h>

int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	/* get line numbers */
	int l = sizeof(art) / sizeof(art[0]);

	/* print repeatedly */
	int i = 0;
	while (1) {
		printf("%s\n", art[i]);
		i++;
		i %= l;
		sleep(1);
	}






	time_measure_end();		/* code end */
	exit(0);
}

