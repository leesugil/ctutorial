/* C template
 * Author: Sugil Steve Lee
 * Last Updated: 2023-12-30 */

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void time_measure_start(void);
void time_measure_end(void);

#define XMAX 1080
#define YMAX 720

struct point {
	int x;
	int y;
};

struct rect {
	struct point pt1;
	struct point pt2;
};

struct point makepoint(int x, int y);

int main(int argc, char *argv[])
{
	time_measure_start();	/* code speed measurement */
	/* actual code
	 * start here */

	struct rect screen;
	struct point middle;
	struct point makepoint(int, int);

	screen.pt1 = makepoint(0, 0);
	screen.pt2 = makepoint(XMAX, YMAX);
	middle = makepoint((screen.pt1.x + screen.pt2.x)/2,
			(screen.pt1.y + screen.pt2.y)/2);

	printf("pt1: (%d, %d), mid: (%d, %d), pt2: (%d, %d)\n", screen.pt1.x, screen.pt1.y, middle.x, middle.y, screen.pt2.x, screen.pt2.y);

	struct point origin, *pp;
	pp = &origin;
	printf("origin is (%d, %d)\n", (*pp).x, pp->y);

	struct rect r, *rp = &r;








	/* end of
	 * actual code */
	time_measure_end();	/* collect time */
	return 0;
}

/* makepoint: make a point from x and y components */
struct point makepoint(int x, int y)
{
	struct point temp;

	temp.x = x;
	temp.y = y;
	return temp;
}

/* addpoints: add two points */
struct point addpoint(struct point p1, struct point p2)
{
	p1.x += p2.x;
	p1.y += p2.y;
	return p1;
}

/* ptinrect: return 1 if p in r, 0 if not */
int ptinrect(struct point p, struct rect r)
{
	return p.x >= r.pt1.x && p.x < r.pt2.x
		&& p.y >= r.pt1.y && p.y < r.pt2.y;
}

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

/* canonrect: canonicalize coordinates of rectangle */
struct rect canonrect(struct rect r)
{
	struct rect temp;

	temp.pt1.x = min(r.pt1.x, r.pt2.x);
	temp.pt1.y = min(r.pt1.y, r.pt2.y);
	temp.pt2.x = max(r.pt1.x, r.pt2.x);
	temp.pt2.y = max(r.pt1.y, r.pt2.y);
	return temp;
}














/* THE CODE BELOW IS
 * RESERVED FOR
 * PERFORMANCE MEASURE */

struct timeval start_wall, end_wall;
double elapsed_time;
clock_t start_cpu, end_cpu;
double cpu_time_used;

void time_measure_start(void)
{
	/* wall-clock time */
	extern struct timeval start_wall, end_wall;
	extern double elapsed_time;

	gettimeofday(&start_wall, NULL);

	/* cpu time */
	extern clock_t start_cpu, end_cpu;
	extern double cpu_time_used;

	start_cpu = clock();
}

void time_measure_end(void)
{
	/* collect cpu time */
	end_cpu = clock();
	cpu_time_used = ((double) (end_cpu - start_cpu)) / CLOCKS_PER_SEC;
	printf("\n\n\t*** END OF CODE ***\n\tCPU time used: %f seconds\n", cpu_time_used);

	/* collect wall-clock time */
	/* collect wall-clock time */
	gettimeofday(&end_wall, NULL);
	elapsed_time = (end_wall.tv_sec - start_wall.tv_sec) + (end_wall.tv_usec - start_wall.tv_usec) / 1000000.0;
	printf("\n\tElapsed wall-clock time: %f seconds\n", elapsed_time);
}

