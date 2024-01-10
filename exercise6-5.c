/* Write a function undef that will remove a name and definition from the table maintained by lookup and install. */

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void time_measure_start(void);
void time_measure_end(void);

#include "table.c"

void undef(char *name, char *defn);
void test_undef(void);

int main(int argc, char *argv[])
{
	time_measure_start();	/* code speed measurement */
	/* actual code
	 * start here */

	test_undef();







	/* end of
	 * actual code */
	time_measure_end();	/* collect time */
	return 0;
}

void undef(char *name, char *defn)
{
	struct nlist *node = lookup(name);

	if (node != NULL)
		if (strcmp(node->defn, defn) == 0)
			hashtab[hash(name)] = NULL;
		else
			printf("(undef) name found in the hashtab but the definition was different.\n");
	else
		printf("(undef) name not found\n");
}

void test_undef(void)
{
	/* install { SG, SUGIL } */
	char *name = "SG";
	char *defn = "SUGIL";
	printf("0 - name: SG, defn: SUGIL\n");
	printf("1 - name: %s, defn: %s\n", name, defn);

	struct nlist *test_node = lookup(name);
	printf("0 - lookup(name): %p\n", NULL);
	printf("1 - lookup(name): %p\n", test_node);

	unsigned i = hash(name);
	printf("0 - hash(name): 18\n");
	printf("1 - hash(name): %u\n", i);

	test_node = install(name, defn);
	printf("0 - lookup(name)->name: SG, lookup(name)->defn: SUGIL\n");
	printf("1 - lookup(name)->name: %s, lookup(name)->defn: %s\n", lookup(name)->name, lookup(name)->defn);

	char *defn2 = "GILSU";
	test_node = install(name, defn2);
	printf("0 - lookup(name)->name: SG, lookup(name)->defn: GILSU\n");
	printf("1 - lookup(name)->name: %s, lookup(name)->defn: %s\n", lookup(name)->name, lookup(name)->defn);

	/* undef { SG, SUGIL } */
	test_node = install(name, defn);
	undef(name, defn);
	printf("0 - lookup(name): %p\n", NULL);
	printf("1 - lookup(name): %p\n", lookup(name));
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
	extern struct timeval start_wall;

	gettimeofday(&start_wall, NULL);

	/* cpu time */
	extern clock_t start_cpu;

	start_cpu = clock();
}

void time_measure_end(void)
{
	/* collect cpu time */
	extern clock_t start_cpu, end_cpu;
	extern double cpu_time_used;
	
	end_cpu = clock();
	cpu_time_used = ((double) (end_cpu - start_cpu)) / CLOCKS_PER_SEC;
	printf("\n\n\t*** END OF CODE ***\n\tCPU time used: %f seconds\n", cpu_time_used);

	/* collect wall-clock time */
	extern struct timeval start_wall, end_wall;
	extern double elapsed_time;

	gettimeofday(&end_wall, NULL);
	elapsed_time = (end_wall.tv_sec - start_wall.tv_sec) + (end_wall.tv_usec - start_wall.tv_usec) / 1000000.0;
	printf("\n\tElapsed wall-clock time: %f seconds\n", elapsed_time);
}

