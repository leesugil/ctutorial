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
			swap4(v, ++last, i);
			swap4(w, ++last, i);
		}
	swap4(v, left, last);
	swap4(w, left, last);
	qsort7(v, left, last-1, reverse, w);
	qsort7(v, last+1, right, reverse, w);
}


/* qsort8: upgrades qsort7, accepts comparison function */
void qsort8(char *v[], int left, int right, int reverse, int (*comp)(void *, void *, int), void *w[])
{
	int i, last, m, r;

	printf("(qsort8) (1)\n");
	if (left >= right)
		return;
	m = (left + right)/2;
	printf("(qsort8) (2) - swap(w, left, m)\n");
	swap5((void *) v, left, m);
	swap5(w, left, m);
	last = left;
	printf("(qsort8) (3) - main comparison\n");
	printf("(qsort8) left+1: %d, right: %d\n", left+1, right);
	for (i = left + 1; i <= right; i++) {
		printf("(qsort8) %d <= %d <= %d, v[%d]: %s\n", left+1, i, right, i, v[i]);
		if ((*comp)(v[i], v[left], reverse) < 0) {
			printf("(qsort8) (4.1) - swapping after comparison to v[left]\n");
			swap5((void *) v, ++last, i);
			swap5(w, ++last, i);
			printf("(qsort8) (4)\n");
		}
		printf("(qsort8) (4.5)\n");
	}
	swap5((void *) v, left, last);
	swap5(w, left, last);
	printf("(qsort8) (5)\n");
	qsort8(v, left, last-1, reverse, comp, w);
	qsort8(v, last+1, right, reverse, comp, w);
	printf("(qsort8) (6)\n");
}
