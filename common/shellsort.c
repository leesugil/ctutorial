#include <stdio.h>
#define	DEBUG	1

/* shellsort: sort v[0], ... v[n-1] into increasing order */
void shellsort(int v[], int n);

main()
{
	int n = 10;
	int v[n];
	int i;

	for (i=0; i<n; i++)
		v[i] = ((i + 100) * 3) % 100;

	printf("Original v[]:\n");
	for (i=0; i<n; i++)
		printf("%3d", v[i]);
	printf("\n");
	shellsort(v, n);
	printf("Shell-sorted v[]:\n");
	for (i=0; i<n; i++)
		printf("%3d", v[i]);
	printf("\n");
}

void shellsort(int v[], int n)
{
	int gap, i, j, temp, k;

	if (DEBUG) {
		printf("Places:\n");
		for (k=0; k<n; k++)
			printf("%3d", k);
		printf("\n");
	}

	for (gap = n/2; gap > 0; gap /= 2)
		for (i = gap; i < n; i++)
			for (j=i-gap; j>=0 && v[j]<v[j+gap]; j-=gap) {
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
				if (DEBUG) {
					for (k=0; k<j; ++k)
						printf("   ");
					printf("  ^");
					for (k=0; k<gap-1; ++k)
						printf("___");
					printf("__^");
					for (k=0; k<(n-gap-j); ++k)
						printf("   ");
					printf("gap: %d, i: %d, j: %d, v[j] = %d, v[j+gap] = %d\n", gap, i, j, v[j], v[j+gap]);
				}
			}
}
