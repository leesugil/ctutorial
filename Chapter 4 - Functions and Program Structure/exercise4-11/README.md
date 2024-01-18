* calc.h
	#define NUMBER '0'
	void push(double);
	double pop(void);
	int getop(char []);
	int getch(void);
	void ungetch(int);
* main.c
	#include <stdio.h>
	#include <stdlib.h>
	#include "calc.h"
	#define MAXOP 100
	main() {
		...
	}
* getop.c
	#include <stdio.h>
	#include <ctype.h>
	#include "calc.h"
	getop() {
		...
	}
* stack.c
	#include <stdio.h>
	#include "calc.h"
	#define MAXVAL 100
	int sp = 0;
	double val[MAXVAL];
	void push(double) {
		...
	}
	double pop(void) {
		...
	}
* getch.c
	#include <stdio.h>
	#define BUFSIZE 100
	char buf[BUFSIZE];
	int bufp = 0;
	int getch(void) {
		...
	}
	void ungetch(int) {
		...
	}
