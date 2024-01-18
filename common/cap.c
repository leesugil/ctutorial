/* Upper / lower case chages */

#include <ctype.h>

char lower(char c)
{
	if (isalpha(c))
		if (isupper(c))
			c += 'a' - 'A';
	return c;
}
