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
