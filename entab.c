#define	TABSTEP	6	/* minimum tab spacing size */
#define	MAXLEN	1000	/* maximum character input size */

void entab(char output[], char input[])
{
	int i, j, k, spaces;

	spaces = 0;
	j = 0;
	k = 0;
	for (i = 0; i < MAXLEN; ++i)
		output[i] = '\0';
	for (i = 0; input[i] != '\0'; ++i) {
		if (input[i] == ' ') {
			++spaces;
		}
		else {
			/* single space */
			if (spaces == 1) {
				output[j] = ' ';
				++j;
			}
			/* multiple spaces */
			else if (spaces > 1) {
				for (k = 0; k < ((spaces - (spaces % TABSTEP)) / TABSTEP) + 1; ++k) {
					output[j] = '\t';
					++j;
				}
			}
			spaces = 0;
			output[j] = input[i];
			++j;
		}
	}
}
