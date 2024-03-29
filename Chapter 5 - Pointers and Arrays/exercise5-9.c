#include <stdio.h>
#include "getline.h"
#include "atoi.h"

#define MAXLINE 100

int day_of_year(int, int, int);
void day_of_year_test(void);
void month_day(int, int, int *, int *);
void month_day_test(void);
char *month_name(int);

main()
{
	day_of_year_test();
	month_day_test();
}

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/* day_of_year: set day of year from month & day */
int day_of_year(int year, int month, int day)
{
	int leap;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	char *p;
	p = daytab[leap];
	while (p - daytab[leap] < month)
		day += *p++;
	return day;
}

void day_of_year_test(void)
{
	int y, m, d;
	char line[MAXLINE];
	printf("(day_of_year) Enter year: ");
	getline2(line, MAXLINE);
	y = atoi(line);
	printf("(day_of_year) Enter month: ");
	getline2(line, MAXLINE);
	m = atoi(line);
	printf("(day_of_year) Enter day: ");
	getline2(line, MAXLINE);
	d = atoi(line);
	printf("(day_of_year) The entered year/month/day is %d/%d/%d. It's the %d'th day of the year.\n", y, m, d, day_of_year(y, m, d));
}

/* month_day: set month, day from day of year */
void month_day(int year, int yearday, int *pmonth, int *pday)
{
	int leap;

	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	char *p;
	p = daytab[leap];
	while (*p++ < yearday)
		yearday -= *(p-1);
	*pmonth = p - 1 - daytab[leap];
	*pday = yearday;
}

void month_day_test(void)
{
	int y, yday, m, d;
	char line[MAXLINE];
	printf("(month_day) Enter year: ");
	getline2(line, MAXLINE);
	y = atoi(line);
	printf("(month_day) Enter yearday: ");
	getline2(line, MAXLINE);
	yday = atoi(line);
	month_day(y, yday, &m, &d);
	printf("(month_day) Entered year/yearday is %d/%d. It's corresponding calendar address is %d/%d/%d.\n", y, yday, y, m, d);
}

/* month_name: return name of n-th month */
char *month_name(int n)
{
	static char *name[] = {
		"Illegal month",
		"January", "February", "March",
		"April", "May", "June",
		"July", "August", "September",
		"October", "November", "December"
	};

	return (n < 1 || n > 12) ? name[0] : name[n];
}
