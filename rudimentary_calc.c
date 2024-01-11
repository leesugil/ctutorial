/* C template
 * Author: Sugil Steve Lee
 * Last Updated: 2024-01-11 */

#include "template_clock.c"

#include <stdio.h>


int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	double sum, v;

	sum = 0;
	while (scanf("%lf", &v) == 1)
		printf("\t%.2f\n", sum += v);








	time_measure_end();		/* code end */
	return 0;
}

