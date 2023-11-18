#include <stdio.h>
#include <ctype.h>
#define MAXLINE	1000

/* atof: convert string s to double */
double atof(char s[])
{
	double val, power, outcome;
	int i, sign, powersign;
	
	for (i = 0; isspace(s[i]); i++)	/* skip white space */
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;	/* skip sign character */
	for (val = 0.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
	}
	if (s[i] = '.')
		i++;	/* skip decimal point character */
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10;
	}
	outcome = sign * val / power;
	/* read the exponential part of scientific notation of the form 123.4e-6 or 123.4E7 */
	if (s[i] == 'e' || s[i] == 'E')
		i++;
	powersign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '-' || s[i] == '+')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	for (i = 0; i < val; i++) {
		if (powersign > 0)
			outcome *= 10;
		else
			outcome /= 10;
	}
	return outcome;
}

main ()
{
	char line[MAXLINE];
	double atof(char []);

	while(getline(line, MAXLINE) > 0) {
		printf("%f\n", atof(line));
	}
}
