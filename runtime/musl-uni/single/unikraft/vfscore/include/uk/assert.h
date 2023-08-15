extern int printf(const char *format, ...);

#define UK_ASSERT(x)	do {} while(0);

#define UK_CRASH(fmt, ...)						\
	do {								\
		printf((fmt), ##__VA_ARGS__);				\
		while(1);						\
	} while (0)

#define uk_pr_crit(fmt, ...)						\
	do {								\
		printf((fmt), ##__VA_ARGS__);				\
	} while (0)


#define uk_pr_info(fmt, ...)						\
	do {								\
		printf((fmt), ##__VA_ARGS__);				\
	} while (0)

#define uk_pr_debug(fmt, ...)						\
	do {								\
	} while (0)


#define uk_pr_warn_once(fmt, ...)						\
	do {								\
	} while (0)


#define uk_pr_err(fmt, ...)						\
	do {								\
		printf((fmt), ##__VA_ARGS__);				\
	} while (0)


