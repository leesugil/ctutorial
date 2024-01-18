#include <stdio.h>
#define	DEBUG	1
#define	MAXLINE	100

/* Write a version of binary search with only one test inside the loop, and measure the difference in run-time. */

/* get_line: outputs a string variable from input */
void get_line(char s[], int lim)
{
	int i, c;

	for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = '\n';
		++i;
	}
	s[i] = '\0';
}

/* progress: returns an integer approximation of the progress percentage of the current state compared to the min and max states. the maximum return is n. returns -1 if the current state is out of bound. */
int progress(int min, int max, int current, int n)
{
	float p;
	int output;
	if (min != max) {
	       	p = (float) (current - min) / (max - min);
		if (DEBUG)
			printf("p: = %d / %d = %f\n", current - min, max - min, p);
	}
	else {
		p = 0;
		if (DEBUG)
			printf("p = 0!!!\n");
	}
	output = (int) (p * ((float) n));
	if (DEBUG) {
		printf("min: %d, max: %d, current: %d, p: %.2f, n: %d, output: %d\n", min, max, current, p, n, output);
	}
	if (p < 0 || 1 < p || n < 1)
		return -1;
	else
		return output;
}

/* checkbits: compares two unsigned integers */
void checkbits(unsigned x, unsigned y)
{
	if (x == y)
		printf("%b == %b\n", x, y);
	else
		printf("%b != %b\n", x, y);
}

/* getbits: get n bits from position p where p=0 is the first rightmost position. */
unsigned getbits(unsigned x, int p, int n)
{
	return (x >> (p+1-n)) & ~(~0 << n);
}

/* setbits: get the rightmost n bits from y and place it starting from position p in x. */
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	y = getbits(y, n-1, n);
	y = y << p+1-n;
	unsigned int m = ~0;
	m = m << p+1;
	m = m + ~(~0 << p+1-n);
	x = x & m;
	x = x + y;
	return x;
}

/* invert(x, p, n) returns x with the n bits that begin at position p inverted, leaving the others unchanged. */
unsigned invert(unsigned x, int p, int n)
{
	return setbits(x, p, n, ~getbits(x, p, n));
}

/* rightrot(x, n) returns the value of the integer x rotated to the right by n positions. */
unsigned rightrot(unsigned x, int n)
{
	int i, p;
	float y = x;

	for (p=0; y >= 2; ++p)
		y = y / 2;
	printf("%b has %d number of bits.\n", x, p+1);
	printf("%b = %b + %b\n", x, getbits(x, n-1, n) << n, getbits(x, p, p+1-n));
	x = (getbits(x, n-1, n) << p+1-n) + getbits(x, p, p+1-n);

	return x;
}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
	int b;

	for (b=0; x != 0; x >>= 1) {
		printf("%d\t%b\n", b, x);
		if (x & 01)
			b++;
	}
	printf("%d\t%b\n", b, x);
	return b;
}

/* bitcount2: a faster version of bitcount */
int bitcount2(unsigned x)
{
	int n = 0;

	printf("%d\t%b\n", n, x);
	while (x != 0) {
		x &= (x-1);
		++n;
		printf("%d\t%b\n", n, x);
	}

	return n;
}

/* lower: converts upper class letters to lower case */
void lower(char s[], int lim)
{
	int i;
	if (DEBUG)
		printf("input: %s\n", s);
	for (i=0; i<lim && s[i] != EOF; ++i)
		('A' <= s[i] && s[i] <= 'Z') ? (s[i] += 'a' - 'A') : (s[i] = s[i]);
	if (DEBUG)
		printf("output: %s\n", s);
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
	int low, mid, high;

	low = 0;
	high = n-1;
	while (low <= high) {
		mid = (low+high)/2;
		if (DEBUG)
			printf("low=%d, high=%d, mid=%d, v[mid]=%d, x=%d\n", low, high, mid, v[mid], x);
		if (x < v[mid])
			high = mid - 1;
		else if (x > v[mid])
			low = mid + 1;
		else	/* found match */
			return mid;
	}
	return -1;	/* no match */
}

/* binsearch2: v[0] <= ... <= v[n-1] */
int binsearch2(int x, int v[], int n)
{
	int low, mid, high;
	
	low = 0;
	high = n - 1;
	while (low < high) {
		mid = (low + high) / 2;
		/* the key is that the loop should converge given that mid will always be rounded down.
		 * if low=0 and high=1, then mid=0 in C.
		 * suppose we use the following criteria:
		 * low <= high,
		 * v[mid] < x.
		 * if x=0, we have ~(v[mid] < x), and want high = mid.
		 * in this case, both low=mid=high=0 at the beginning of the next loop.
		 * this is ~(v[mid] < x) again, and high = mid does not change anything, making the while loop infinite.
		 * if x=1, we have v[mid] < x, and want low = mid+1. (obsolute to discuss)
		 * suppose we use the criterion
		 * v[mid] <= x.
		 * if x=0, we have v[mid] <= x, so we want low = mid.
		 * at the beginning of the next loop, we have low=0, high=1 again, making the loop infinite.
		 * thus we should correct the while loop condition from the beginning. suppose we use
		 * low < high
		 * for the while loop condition.
		 * and suppose we use
		 * v[mid] < x
		 * for the if condition.
		 * consider the same low=0 high=1 situation. (hence mid=0)
		 * if x=0, we have ~(v[mid] < x), thus want high = mid = 0.
		 * this breaks low < high, and x == v[mid_old] == v[mid_new].
		 * if x=1, we have v[mid] < x, thus want low = mid+1.
		 * this also breaks low < high, and x == v[mid_new].
		 * thus if we use mid_new, the problem is solved.*/
		if (DEBUG)
			printf("low=%d, high=%d, mid=%d, v[mid]=%d, x=%d\n", low, high, mid, v[mid], x);
		if (v[mid] < x)
			low = mid+1;
		else
			high = mid;
	}
	mid = (low+high)/2;
	if (DEBUG)
		printf("x=%d, v[mid]=%d\n", x, v[mid]);
	if (x == v[mid])
		return mid;
	else
		return -1;
}

main() {
	/* code start here */
	int x = 0;
	int n = 23523;
	int v[n];

	for (int i=0; i<n; ++i)
		v[i] = ((3*i*i) % 72) * 44;

	printf("x = %d, v[i] = %d\n", x, v[binsearch(x, v, n)]);
	printf("x = %d, v[i] = %d\n", x, v[binsearch2(x, v, n)]);
}
