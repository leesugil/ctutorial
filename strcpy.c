/* strcpy2: copy t to s; pointer version */
void strcpy2(char *s, char *t)
{
	while ((*s++ = *t++) != '\0')
		;
}
