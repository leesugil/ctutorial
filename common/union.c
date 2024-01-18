union u_tag {
	int ival;
	float fval;
	char *sval;
} u;

#define NSYM 100

struct {
	char *name;
	int flags;
	int utype;
	union {
		int ival;
		float fval;
		char *sval;
	} u;
} symtab[NSYM];
