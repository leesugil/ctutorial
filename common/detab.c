/* detab: replaces tabs in the input with the proper number of blanks to space to the next tab stop. */
/* Example:
 * TABSTEP: 5
 * \tab\tcd e\tf
 * 01234567890123456789
 *      ab   cd e f */
void detab(char *output, char *input, int *tabstop)
{
	int i, n, p = 0;	/* tracks current position count of the output */
	while (*input++ != '\0') {
		if (*(input-1) == '\t') {
			n = TABSTEP - (p % TABSTEP);
			for (i = 0; i < n; i++, p++)
				*output++ = ' ';
		}
		else {
			*output++ = *(input-1);
			p++;
		}
	}
}
