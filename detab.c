#define	TABSTEP	6	/* minimum tab spacing size */
#define	MAXLEN	1000	/* maximum character input size */

void detab(char output[], char input[])
{
	int i, j;

	j = 0;
	for (i = 0; input[i] != '\0'; ++i) {
		if (j < MAXLEN - 1) {
			if (input[i] == '\t') {
				/* detab here */
				output[j] = ' ';
				++j;
				while (j % TABSTEP != 0) {
					if (j < MAXLEN - 1) {
						output[j] = ' ';
						++j;
					}
				}
			}
			else {
				output[j] = input[i];
				++j;
			}
		}
	}
	output[j] = '\0';
}
