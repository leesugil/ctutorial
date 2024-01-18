/* Write a private version of scanf analogous to minprintf from the previous section. */

#include "template_clock.c"

#include <stdarg.h>

void minscanf(char *fmt, ...);

int main(int argc, char *argv[])
{
	time_measure_start();	/* code start */

	int day, month, year;
	char monthname[20];

	char s[] = "5/12/1984";
	char s2[] = "%d/%d/%d";

	sscanf(s, s2, &month, &day, &year);

	printf("mm/dd/yy: %.2d/%.2d/%.2d\n", month, day, year % 100);

	printf("\n--- beginning of minscanf ---\n");

	minscanf(s2);





	time_measure_end();		/* code end */
	return 0;
}

void minscanf(char *fmt, ...)
{
	va_list ap;
	char *p;
	char *sval;
	int ival;
	double dval;

	va_start(ap, fmt);
	/* fmt: "%d/%d/%d" */
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			*p = getchar();
			continue;
		}
		switch (*++p) {
			case 'd':
				printf("case 'd'\n");
				ival = va_arg(ap, int);
				scanf("%d", &ival);
				printf("%d", ival);
				break;
			case 'f':
				printf("case 'f'\n");
				dval = va_arg(ap, double);
				scanf("%lf", &dval);
				printf("%lf", dval);
				break;
			case 's':
				printf("case 's'\n");
				for (sval = va_arg(ap, char *); *sval; sval++)
					*sval = getchar();
				printf("%s", sval);
				break;
			default:
				printf("case default\n");
				*p = getchar();
				break;
		}
	}
	va_end(ap);
}
