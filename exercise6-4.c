/* Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurence. Precede each word by its count. */

/* approach: this looks like sorting a sorted outcome with a different criteria, and adding increase/decrease option.
 * the original output from the tree structure gives the output in alphabetical order, yet already preceded by counts. we want to apply descending sort just to these counts, yet not affecting the alphabetical order of the already-sorted tree structure.
 * we detect the first space following the count to be the separating value, apply qsort on the outcome in the first field only.
 * in order to do that, we first mute the original treerecord.
 * instead, treerecord will record the outcome in an array of pointers to a new structure made of two fields, count and word.
 * then apply qsort to the array with the count field.
 *
 * one non-trivial thing here is to define an array of pointers first before recording in it using treerecord. we need to determine the length of the tree first to define such array.
 * to implement it, set a counter to count the length each time a node is added. such induced array will sufficiently secure the memory even when we apply filter on the output later which is not the main issue at the moment. */

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void time_measure_start(void);
void time_measure_end(void);


struct tnode {				/* the tree node: */
	char *word;				/* points to the text */
	int count;				/* number of occurrences */
	struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};

struct output {
	char *word;
	int count;
};

#include <ctype.h>
#include <string.h>
#include "ungetch.c"
#include "qsort.c"
#include "itoa.c"

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *, int *);
void treerecord(struct tnode *, struct output *[]);
void createoutput(struct output *[], int);
void outputprint(struct output *[], int);
int getword(char *, int);

/* word frequency count */
int main(int argc, char *argv[])
{
	time_measure_start();	/* code speed measurement */
	/* actual code
	 * start here */

	struct tnode *root;
	char word[MAXWORD];
	int tree_length = 0;
	struct output *o[tree_length];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word, &tree_length);
	createoutput(o, tree_length);
	treerecord(root, o);
	outputprint(o, tree_length);








	/* end of
	 * actual code */
	time_measure_end();	/* collect time */
	return 0;
}

struct tnode *talloc(void);
char *strdup2(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, int *tree_length)
{
	int cond;

	if (p == NULL) {		/* a new word has arrived */
		p = talloc();		/* make a new node */
		p->word = strdup2(w);
		p->count = 1;
		p->left = p->right = NULL;
		(*tree_length)++;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;			/* repeated word */
	else if (cond < 0)		/* less than into left subtree */
		p->left = addtree(p->left, w, tree_length);
	else					/* greater than into right subtree */
		p->right = addtree(p->right, w, tree_length);
	return p;
}

/* treerecord: in-order record of tree p */
void treerecord(struct tnode *p, struct output *o[])
{
	static int i = 0;
	if (p != NULL) {
		treerecord(p->left, o);
		o[i]->count = p->count;
		o[i]->word = p->word;
		i++;
		treerecord(p->right, o);
	}
}

#include <stdlib.h>

/* talloc: make a tnode */
struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup2(char *s)	/* make a duplicate of s */
{
	char *p;

	p = (char *) malloc(strlen(s)+1);	/* +1 for '\0' */
	if (p != NULL)
		strcpy(p, s);
	return p;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;

	while (isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for ( ; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

/* outputprint: prints output */
void outputprint(struct output *o[], int length)
{
	printf("count\tword\n");
	int i;
	for (i = 0; i < length; i++)
		printf("%d\t%s\n", o[i]->count, o[i]->word);
}

struct output *oalloc(void)
{
	return (struct output *) malloc(sizeof(struct output));
}

/* createoutput: allocate memory to an empty struct output */
void createoutput(struct output *p[], int length)
{
	int i;
	for (i = 0; i < length; i++) {
		p[i] = oalloc();
		p[i]->count = 0;
		p[i]->word = NULL;
	}
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
