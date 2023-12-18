#include "swap.c"

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

