/* entab: replace strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. */
/* Example:
 * TABSTEP: 5
 * ab      cd  ef         g
 * 012345678901234567890123456789
 * ab\t ...cd..ef\t    ...g       */
/* the code needs to be updated as each time tab is used, tab stops should be considered */
void entab(char *output, char *input, int *tabstop)
{
	int i, n, p = 0, spaces = 0;
	while (*input++ != '\0') {
		if (*(input-1) == ' ') {
			spaces++;
		}
		else if (*(input-1) == '\t') {
			spaces += TABSTEP;
		}
		else {
			if (spaces > 0) {
				n = TABSTEP - (p % TABSTEP);
				if (n <= spaces) {
					*output++ = '\t';
					p += n;
					spaces -= n;
				}
				while (spaces >= TABSTEP) {
					*output++ = '\t';
					p += TABSTEP;
					spaces -= TABSTEP;
				}
				while (spaces-- > 0) {
					*output++ = ' ';
					p++;
				}
				spaces = 0;
			}
			*output++ = *(input-1);
			p++;
		}
	}
}
