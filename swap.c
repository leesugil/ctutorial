/* swap: interchange v[i] and v[j] */
void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* swap2: interchange v[i] and v[j], pointer version */
void swap2(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* swap3: exchanges two pointers */
void swap3(void *v[], int i, int j)
{
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* swap4: upgrades swap2, shifting */
void swap4(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
	int s = (i <= j) ? i : j;
	int l = (i <= j) ? j : i;
	int k;
	for (k = s; k < l; k++)
		swap2(v, k, k+1);
}

/* swap5: upgrades swap4, accepts void* */
void swap5(void *v[], int i, int j)
{
	void *temp;

	printf("(swap5) (1)\n");
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
	printf("(swap5) (2)\n");
	int s = (i <= j) ? i : j;
	int l = (i <= j) ? j : i;
	int k;
	printf("(swap5) (3), s = %d, l = %d\n", s, l);
	for (k = s; k < l; k++) {
		swap3(v, k, k+1);
		printf("(swap5) (3.5) - swapped\n");
	}
	printf("(swap5) (4)\n");
}

