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
	printf("\t(swap3) swapping %d and %d\n", i, j);
	void *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

/* swap4: upgrades swap2, shifting */
void swap4(char *v[], int i, int j)
{
	int s = (i <= j) ? i : j;
	int l = (i <= j) ? j : i;
	int k;
	for (k = s; k < l; k++)
		swap2(v, k, k+1);
}

/* swap5: upgrades swap4, accepts void */
void swap5(void *v[], int i, int j)
{
	int s = (i <= j) ? i : j;
	int l = (i <= j) ? j : i;
	int k;
	for (k = s; k < l; k++)
		swap3(v, k, k+1);
}

