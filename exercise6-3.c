/* Write a cross-referencer that prints a list of all words in a document, and for each word, a list of the line numbers on which it occurs. Remove noise words like "the," "and," and so on. */

/* approach: the main point is that the length of the list of line numbers is not pre-determined. define another binary tree structure with members as line_number, line_left, line_right and create a root tree for each word.
 * detect '\n' to count line numbers.
 * create a list of noise words and apply it as a filter. */

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void time_measure_start(void);
void time_measure_end(void);


struct tnode_line {
	int line_number;
	struct tnode_line *left;
	struct tnode_line *right;
};

struct tnode {				/* the tree node: */
	char *word;				/* points to the text */
	int count;				/* number of occurrences */
	struct tnode_line line_num;		/* root of line number nodes */
	struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};


#include <ctype.h>
#include <string.h>
#include "getword.c"

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
struct tnode_line *addtree_line(struct tnode_line *, int num);
void treeprint(struct tnode *);
void treeprint_line(struct tnode_line *);

/* word frequency count */
int main(int argc, char *argv[])
{
	time_measure_start();	/* code speed measurement */
	/* actual code
	 * start here */

	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	treeprint(root);








	/* end of
	 * actual code */
	time_measure_end();	/* collect time */
	return 0;
}

struct tnode *talloc(void);
char *strdup2(char *);

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;

	if (p == NULL) {		/* a new word has arrived */
		p = talloc();		/* make a new node */
		p->word = strdup2(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;			/* repeated word */
	else if (cond < 0)		/* less than into left subtree */
		p->left = addtree(p->left, w);
	else					/* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
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
