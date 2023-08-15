#include <time.h>

int days_in_month(int, int);
int month_to_secs(int, int);
long long year_to_secs(long long, int *);
long long tm_to_secs(const struct tm *);
const char *tm_to_tzname(const struct tm *);
int secs_to_tm(long long, struct tm *);
void secs_to_zone(long long, int, int *, long *, long *, const char **);
const char *strftime_fmt_1(char (*)[100], size_t *, int, const struct tm *, locale_t, int);
extern  const char utc[];

