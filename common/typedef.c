typedef int Length;
typedef char *String;
typedef struct tnode *Treeptr;
typedef struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
} Treenode;
typedef int (*PFI)(char *, char *);

#include <stdio.h>

int main()
{
	Treeptr p = NULL;
	printf("Treeptr p: %p\n", p);
}
