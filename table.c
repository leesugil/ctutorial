struct nlist {				/* table entry: */
	struct nlist *next;		/* next entry in chain */
	char *name;				/* defined name */
	char *defn;				/* replacement text */
};

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];	/* pointer table */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

/* lookup: look for s in hastab */
struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hastab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np-<name) == 0)
			return np;
	return NULL;
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];	/* np->next takes over the old head of the list at hashtab[hashval] */
		hashtab[hashval] = np;	/* np is the new head of the list at hashtab[hashval] */
	} else
		free((void *) np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}
