#include <stdio.h>

#define MAXLINE	1000

main ()
{
	char line[MAXLINE];
	double atof(char []);

	while(getline(line, MAXLINE) > 0) {
		printf("%f\n", atof(line));
	}
}
