/* Write a program that reads a C program and prints in alphabetical order each group of variable names that are identical in the first 6 characters, but different somewhere thereafter. Don't count words within strings and comments. Make 6 a parameter that can be set from the command line. */

/* Main approach: upgrade the existing code by providing a conditional partial-sum (a "group-by" sum) feature with filtering. To do that, add a group member to tnode called "var". To detect variable names only and ignoring strings and comments, add a function to classify them and let the outcome determine ".var". When producing an output, add a feature to partial-sum by the first n=6 characters, filtered by ".var == some-valid-value". */

/* challenge: sorting might get messy with the above method. we'll have "{x, var}", "{x, non-var}" at the same time, and the tree would become no longer binary (or we'd have another tree solely for variable names). */

/* update: instead of adding ".var", add ".var_count" to count variable names seperately. */

/* C template
 * Author: Sugil Steve Lee
 * Last Updated: 2023-12-30 */

#include <stdio.h>
#include <sys/time.h>
#include <time.h>

void time_measure_start(void);
void time_measure_end(void);


struct tnode {				/* the tree node: */
	char *word;				/* points to the text */
	int count;				/* number of occurrences */
	int var_count;			/* variable name occurences */
	struct tnode *left;		/* left child */
	struct tnode *right;	/* right child */
};

#include <ctype.h>
#include <string.h>
#include "getword.c"

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);
void update_is_c_var(char *);
char is_c_var = 0;			/* 1 if a variable name */
char in_comment = 0;		/* 1 if in comment */
char in_string = 0;			/* 1 if in strinf */

/* word frequency count */
int main(int argc, char *argv[])
{
	time_measure_start();	/* code speed measurement */
	/* actual code
	 * start here */

	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF) {
		update_is_c_var(word);
		if (isalpha(word[0]))
			root = addtree(root, word);
	}
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
		p->var_count = (is_c_var) ? 1 : 0;
		p->count = (is_c_var) ? 0 : 1;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		if (is_c_var)
			p->var_count++;
		else
			p->count++;		/* repeated word */
	else if (cond < 0)		/* less than into left subtree */
		p->left = addtree(p->left, w);
	else					/* greater than into right subtree */
		p->right = addtree(p->right, w);
	return p;
}

char *vtype[] = {
	"char",
	"int",
	"double",
	"long"
};
int length = sizeof(vtype) / sizeof(vtype[0]);

int is_in_string(char *);
int is_in_comment(char *);

/* update_is_c_var: updates is_c_var and within_string_or_comment */
void update_is_c_var(char *w)
{
	/* strings */
	/* comments */
	/* declaration keyword and ;*/
	static int declaration = 0;		/* 1 if in declaration mode */
	int i;
	if (!is_in_string(w) && !is_in_comment(w)) {
		if (declaration == 0) {
			for (i = 0; i < length; i++)
				if (strcmp(w, vtype[i]) == 0)
					declaration = 1;
		}
		else if (w[0] == ';')
			declaration = 0;
	}
	/* strings, comments */
	is_c_var = (declaration) ? 1 : 0;
}

/* is_in_string: detects " but avoids \" */
int is_in_string(char *w)
{
	/* should be ignored when in comment */
	static char p_char = '\0';
	if (!in_comment) {
		if (in_string == 0 && w[0] == '\"')
			in_string = 1;
		else if (in_string == 1
				&& p_char != '\\'
				&& w[0] == '\"')
			in_string = 0;
	}
	p_char = w[0];
	return in_string;
}

/* is_in_comment: detects \/\* and \/\* */
int is_in_comment(char *w)
{
	/* should be ignored when in string */
	static char p_char = '\0';
	if(!in_string) {
		if (in_comment == 0
				&& p_char == '/'
				&& w[0] == '*')
			in_comment = 1;
		else if (in_comment == 1
				&& p_char == '*'
				&& w[0] == '/')
			in_comment = 0;
	}
	p_char = w[0];
	return in_comment;
}

void process_node(struct tnode *);

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
	static char header = 1;
	if (header == 1) {
		printf("word\tcount\tvar_count\n");
		header = 0;
	}
	if (p != NULL) {
		treeprint(p->left);
		process_node(p);
		treeprint(p->right);
	}
}

void process_node(struct tnode *p)
{
	printf("%s\t%4d\t%4d\n", p->word, p->count, p->var_count);
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

