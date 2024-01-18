#include "swap.c"
#include "cmp.c"

/* qsort2: sort v[left], ..., v[right] into increasing order, pointer version */
void qsort2(char *v[], int left, int right)
{
	int i, last;

	if (left >= right)
		return;
	swap2(v, left, (left + right)/2);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap2(v, ++last, i);
	swap2(v, left, last);
	qsort2(v, left, last-1);
	qsort2(v, last+1, right);
}

/* qsort3: sort v[left]...v[right] into increasing order. accepts comparison method as an argument. */
void qsort3(void *v[], int left, int right, int (*comp)(void *, void *))
{
	int i, last;

	if (left >= right)	/* do nothing if array contains */
		return;	/* fewer than two elements */
	swap3(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((*comp)(v[i], v[left]) < 0)
			swap3(v, ++last, i);
	swap3(v, left, last);
	qsort3(v, left, last-1, comp);
	qsort3(v, last+1, right, comp);
}

/* qsort4: sort v[left]...v[right] into increasing order. upgrades qsort3. provides reverse sorting. */
void qsort4(void *v[], int left, int right, int reverse, int (*comp)(void *, void *))
{
	int i, r, last;
	r = 1 - (2 * reverse);

	if (left >= right)	/* do nothing if array contains */
		return;	/* fewer than two elements */
	swap3(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (r * (*comp)(v[i], v[left]) < 0)
			swap3(v, ++last, i);
	swap3(v, left, last);
	qsort4(v, left, last-1, reverse, comp);
	qsort4(v, last+1, right, reverse, comp);
}

/* qsort5: sort v[left]...v[right] into increasing order. accepts comparion function, reverse, fold. upgrades qsort4. */
void qsort5(void *v[], int left, int right, int reverse, int fold, int (*comp)(void *, void *, int, int))
{
	int i, d, last;

	if (left >= right)
		return;
	if ((*comp)(v[left], v[(left + right) / 2], reverse, fold) > 0)
		swap3(v, left, (left + right) / 2);
	last = left;
	for (i = left+1; i <= right; i++)
		if ((d = (*comp)(v[i], v[left], reverse, fold)) < 0)
			swap3(v, ++last, i);
	swap3(v, left, last);
	qsort5(v, left, last-1, reverse, fold, comp);
	qsort5(v, last+1, right, reverse, fold, comp);
}

/* qsort6: upgrades qsort2, accepts reverse */
void qsort6(char *v[], int left, int right, int reverse)
{
	int i, last, m, r;
	r = 1 - 2 * reverse;

	if (left >= right)
		return;
	m = (left + right)/2;
	swap4(v, left, m);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (r * strcmp(v[i], v[left]) < 0)
			swap4(v, ++last, i);
	swap4(v, left, last);
	qsort6(v, left, last-1, reverse);
	qsort6(v, last+1, right, reverse);
}

/* qsort7: upgrades qsort6, accepts second array */
void qsort7(char *v[], int left, int right, int reverse, char *w[])
{
	int i, last, m, r;
	r = 1 - 2 * reverse;

	if (left >= right)
		return;
	m = (left + right)/2;
	swap4(v, left, m);
	swap4(w, left, m);
	last = left;
	for (i = left + 1; i <= right; i++)
		if (r * strcmp(v[i], v[left]) < 0) {
			swap4(v, last, i);
			swap4(w, ++last, i);
		}
	swap4(v, left, last);
	swap4(w, left, last);
	qsort7(v, left, last-1, reverse, w);
	qsort7(v, last+1, right, reverse, w);
}

void display_status(int *[], int, int);
void display_change(int *[], int, int);

/* qsort8: upgrades qsort7, uses swap5, accepts void */
void qsort8(void *v[], int left, int right, int reverse, void *w[])
{
	printf("-----------(1)\n");
	display_status((int **) v, left, right);
	int i, last, m;

	if (left >= right)
		return;
	m = (left + right)/2;
	swap3(v, left, m);
	swap3(w, left, m);
	display_change((int **) v, left, m);
	last = left;
	printf("-----------(2)\n");
	for (i = left+1; i <= right; i++)
		if (numcmp2(v[i], v[left], reverse) < 0) {
			swap3(v, ++last, i);
			swap3(w, last, i);
			display_change((int **) v, last, i);
		}
	printf("-----------(3)\n");
	swap3(v, left, last);
	swap3(w, left, last);
	display_change((int **) v, left, last);
	qsort8(v, left, last-1, reverse, w);
	qsort8(v, last+1, right, reverse, w);
}

void display_status(int *v[], int left, int right)
{
	int i;
	for (i = 0; i < left; i++)
		printf("  ");
	for(i = left; i <= right; i++)
		printf(" %d", *v[i] - '0');
	printf("\n");
}

void display_change(int *v[], int left, int right)
{
	int i;
	for (i = 0; i < left; i++)
		printf("  ");
	printf(" ^");
	for (i = left + 1; i < right; i++)
		printf("--");
	printf("-^\n");

	for (i = 0; i < left; i++)
		printf("  ");
	printf(" %d", *v[i] - '0');
	for (i = left + 1; i < right; i++)
		printf("  ");
	printf(" %d\n", *v[i] - '0');
}
