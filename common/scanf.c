/* C template
 * Author: Sugil Steve Lee
 * Last Updated: 2024-01-11 */

#include "template_clock.c"



int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	/* 25 Dec 1988 */
	char s[] = "25 Dec 1988";
	int day, year;
	char monthname[20];

	sscanf(s, "%d %s %d", &day, monthname, &year);
	printf("%d %s %d\n", day, monthname, year);

	int month;
	char s2[] = "12/25/1988";
	sscanf(s2, "%d/%d/%d", &month, &day, &year);
	printf("%d/%d/%d\n", month, day, year);

	char *line = NULL;
	size_t len = 0;

	while (getline(&line, &len, stdin) > 0) {
		if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)
			printf("valid: %s\n", line);
		else if (sscanf(line, "%d/%d/%d", &month, &day, &year) == 3)
			printf("valid: %s\n", line);
		else
			printf("invald: %s\n", line);
	}





	time_measure_end();		/* code end */
	return 0;
}

