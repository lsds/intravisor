#ifndef __UK_MUTEX_H__
#define __UK_MUTEX_H__


struct uk_mutex {
	int lock_count;
	void *owner;
	void *wait;
};

#define	UK_MUTEX_INITIALIZER(name)				\
	{ 0, NULL, NULL }

#define uk_mutex_lock(a)	do{} while(0)
#define uk_mutex_unlock(a)	do{} while(0)

#endif /* __UK_MUTEX_H__ */