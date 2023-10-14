#include <stdio.h>
#include <string.h>
#define	DEBUG	1

/* write a function expand(s1, s2) that expands shorthand notations like a-z in the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange that a leading or trailing - is taken literally. */

void expand(char s1[], char s2[]);

main()
{
	int i, n;
	char s1[] = "a-f-z";
	n = (((strlen(s1) / 2) + 1) * 26) + 1;
	char s2[n];

	for (i = 0; i < n; i++)
		s2[i] = 0;
	printf("Before: %s\n", s1);
	expand(s1, s2);
	printf("After: %s\n", s2);
}

void expand(char s1[], char s2[]) {
	/* set s2[j] = s1[i], i++, j++
	 * if s1[i-2], s1[i-1], s1[i] give a pattern "a-z", then j -> j-2 and then expand. */
	int i, j, k;

	for (i = 0, j = 0; i < strlen(s1); i++, j++) {
		s2[j] = s1[i];
		if (i > 1 && s1[i-1] == '-') {
			if (DEBUG)
				printf("aha! '-' here!\n%c %c %c\n", s1[i-2], s1[i-1], s1[i]);
			/* detect if 'a' <= s1[i-2] <= s1[i] <= 'z'
			 * j -> j-2
			 * 0 <= k <= s1[i] - s1[i-2]
			 * j -> j + k
			 * s2[j] = s1[i-2] + k
			 * note that this algorithm is prone to the a-b-c pattern. */
			if ('a' <= s1[i-2] && s1[i-2] <= s1[i] && s1[i] <= 'z') {
				if (DEBUG)
					printf("aha! 'a' <= ... <= 'z'\ni: %d j: %d\n2: s\n",i , j, s2);
				j = j-2;
				for (k=1; k <= s1[i] - s1[i-2]; k++)
					s2[j + k] = s1[i-2] + k;
				j = j + k;
			}
		}
	}
	s2[j] = '\0';
}
