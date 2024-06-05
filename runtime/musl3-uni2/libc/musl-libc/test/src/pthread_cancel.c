#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Test matrices
//
// Cancellation enabled
//         |     Type      |
//  At CP? | ASYNC | DEFER |
// --------|-------|-------|
//      NO |  T-1  |  T-3  |
// --------|-------|-------|
//     YES |  T-2  |  T-4  |
// --------|-------|-------|
//
// Cancellation disabled
// |     Type      |
// | ASYNC | DEFER |
// |-------|-------|
// |  T-5  |  T-6  |
// |-------|-------|
//
// Cancellation masked (extension)
// |     Type      |
// | ASYNC | DEFER |
// |-------|-------|
// |  T-7  |  T-8  |
// |-------|-------|

#define T(__expr, __msg)                                                       \
  if (!!(__expr)) {                                                            \
    printf("%s at line %d.\n", (__msg), (__LINE__));                           \
    exit(1);                                                                   \
  }

#define ASTR(__obj, __val) __atomic_store_n(&(__obj), (__val), __ATOMIC_RELAXED)

#define ALDR(__obj) __atomic_load_n(&(__obj), __ATOMIC_RELAXED)

static sem_t sem;
static int checkpoint = 0;

// T-1
// Test asynchronous cancellation
// In this case the thread being cancelled should ~immediately be terminated
// regardless of what it is executing (more or less).
void *test_cancel_async_no_cp(void *arg) {
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  T(sem_post(&sem), "sem_post failed");
  // There is no cancellation point here
  for (;;) {
    sched_yield();
  }
  ASTR(checkpoint, 1);
  return NULL;
}

static int cancel_async_no_cp() {
  T(sem_init(&sem, 0, 0), "sem_init failed");
  void *thread_ret = 0;
  ASTR(checkpoint, 0);
  pthread_t thread;
  pthread_create(&thread, NULL, test_cancel_async_no_cp, NULL);
  T(sem_wait(&sem), "sem_wait failed");
  T(sleep(1), "sleep failed");
  pthread_cancel(thread);
  pthread_join(thread, &thread_ret);
  T(thread_ret != PTHREAD_CANCELED, "Thread exit code is not PTHREAD_CANCELED");
  T(0 != ALDR(checkpoint), "Thread reached checkpoint 1");
  return 0;
}

// T-2
// Test asynchronous cancellation
// In this case the thread being cancelled should ~immediately be terminated
// regardless of what it is executing (more or less).
void *test_cancel_async_in_cp(void *arg) {
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  T(sem_post(&sem), "sem_post failed");
  sleep(100);
  ASTR(checkpoint, 1);
  return NULL;
}

static int cancel_async_in_cp() {
  void *thread_ret = 0;
  ASTR(checkpoint, 0);
  pthread_t thread;
  pthread_create(&thread, NULL, test_cancel_async_in_cp, NULL);
  T(sem_wait(&sem), "sem_wait failed");
  T(sleep(1), "sleep failed");
  pthread_cancel(thread);
  pthread_join(thread, &thread_ret);
  T(thread_ret != PTHREAD_CANCELED, "Thread exit code is not PTHREAD_CANCELED");
  T(0 != ALDR(checkpoint), "Thread reached checkpoint 1");
  return 0;
}

// T-3
// Test deferred cancellation in a case where thread is NOT "in cp".
// In this case the thread being cancelled should terminate ~immediately.
void *test_cancel_deferred_no_cp(void *arg) {
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
  T(sem_post(&sem), "sem_post failed");
  // There is no cancellation point here
  while (0 == ALDR(checkpoint)) {
    sched_yield();
  }
  ASTR(checkpoint, 2);
  // Cancellation point
  sleep(100);
  ASTR(checkpoint, 3);
  return NULL;
}

static int cancel_deferred_no_cp() {
  void *thread_ret = 0;
  ASTR(checkpoint, 0);
  pthread_t thread;
  pthread_create(&thread, NULL, test_cancel_deferred_no_cp, NULL);
  T(sem_wait(&sem), "sem_wait failed");
  T(sleep(1), "sleep failed");
  pthread_cancel(thread);
  ASTR(checkpoint, 1);
  pthread_join(thread, &thread_ret);
  T(thread_ret != PTHREAD_CANCELED, "Thread exit code is not PTHREAD_CANCELED");
  T(2 != ALDR(checkpoint), "Thread didn't reach checkpoint 2");
  return 0;
}

// T-4
// Test deferred cancellation in a case where thread is "in cp".
// In this case the thread being cancelled should terminate ~immediately.
void *test_cancel_deferred_in_cp(void *arg) {
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
  T(sem_post(&sem), "sem_post failed");
  errno = 0;
  sleep(100);
  T(errno == -ECANCELED, "Expected -ECANCELED");
  sleep(1);
  T(1, "Should not get here");
  return NULL;
}

static int cancel_deferred_in_cp() {
  void *thread_ret = 0;
  pthread_t thread;
  pthread_create(&thread, NULL, test_cancel_deferred_in_cp, NULL);
  T(sem_wait(&sem), "sem_wait failed");
  T(sleep(1), "sleep failed");
  pthread_cancel(thread);
  pthread_join(thread, &thread_ret);
  T(thread_ret != PTHREAD_CANCELED, "Thread exit code is not PTHREAD_CANCELED");
  return 0;
}

// T-5
// Test asynchronous cancellation when cancellations are disabled.
void *test_cancel_async_disabled(void *arg) {
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  // Should not get cancelled in this scope.
  {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    T(sem_post(&sem), "sem_post failed");
    ASTR(checkpoint, 1);
    while (1 == ALDR(checkpoint))
      sched_yield();
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    ASTR(checkpoint, 3);
  }
  sleep(100);
  T(1, "Should not get here");
  return NULL;
}

static int cancel_async_disabled() {
  void *thread_ret = 0;
  ASTR(checkpoint, 0);
  pthread_t thread;
  pthread_create(&thread, NULL, test_cancel_async_disabled, NULL);
  T(sem_wait(&sem), "sem_wait failed");
  T(sleep(1), "sleep failed");
  T(1 != ALDR(checkpoint), "Thread did something wrong");
  pthread_cancel(thread);
  ASTR(checkpoint, 2);
  pthread_join(thread, &thread_ret);
  T(thread_ret != PTHREAD_CANCELED, "Thread exit code is not PTHREAD_CANCELED");
  T(3 != ALDR(checkpoint), "Thread did something wrong");
  return 0;
}

// T-6
// Test deferred cancellation when cancellations are disabled.
void *test_cancel_deferred_disabled(void *arg) {
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
  // Should not get cancelled in this scope.
  {
    pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
    T(sem_post(&sem), "sem_post failed");
    ASTR(checkpoint, 1);
    while (1 == ALDR(checkpoint))
      sched_yield();
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    ASTR(checkpoint, 3);
  }
  sleep(100);
  T(1, "Should not get here");
  return NULL;
}

static int cancel_deferred_disabled() {
  void *thread_ret = 0;
  ASTR(checkpoint, 0);
  pthread_t thread;
  pthread_create(&thread, NULL, test_cancel_deferred_disabled, NULL);
  T(sem_wait(&sem), "sem_wait failed");
  T(sleep(1), "sleep failed");
  T(1 != ALDR(checkpoint), "Thread did something wrong");
  pthread_cancel(thread);
  ASTR(checkpoint, 2);
  pthread_join(thread, &thread_ret);
  T(thread_ret != PTHREAD_CANCELED, "Thread exit code is not PTHREAD_CANCELED");
  T(3 != ALDR(checkpoint), "Thread did something wrong");
  return 0;
}

// T-7
// Test asynchronous cancellation when cancellations are masked.
// This is a musl-libc extension
void *test_cancel_async_masked(void *arg) {
  pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  pthread_setcancelstate(PTHREAD_CANCEL_MASKED, NULL);
  T(sem_post(&sem), "sem_post failed");
  errno = 0;
  sleep(100);
  T(1, "Should not get here");
  return 0;
}

static int cancel_async_masked() {
  void *thread_ret = 0;
  ASTR(checkpoint, 0);
  pthread_t thread;
  pthread_create(&thread, NULL, test_cancel_async_masked, NULL);
  T(sem_wait(&sem), "sem_wait failed");
  T(sleep(1), "sleep failed");
  pthread_cancel(thread);
  pthread_join(thread, &thread_ret);
  T(thread_ret != PTHREAD_CANCELED, "Thread exit code is not PTHREAD_CANCELED");
  return 0;
}

// T-9
// TBD
void *test_cancel_deferred_in_cp_custom(void *arg) {
  pthread_mutex_t mutex;
  pthread_cond_t cond;

  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

  pthread_mutex_init(&mutex, NULL);
  pthread_cond_init(&cond, NULL);

  pthread_mutex_lock(&mutex);

  T(sem_post(&sem), "sem_post failed");
  pthread_cond_timedwait(&cond, &mutex, NULL);

  T(1, "Should not get here");
  return NULL;
}

static int cancel_deferred_in_cp_custom() {
  void *thread_ret = 0;
  pthread_t thread;
  for (int i = 0; i < 1000; i++) {
    pthread_create(&thread, NULL, test_cancel_deferred_in_cp_custom, NULL);
    T(sem_wait(&sem), "sem_wait failed");
    pthread_cancel(thread);
    pthread_join(thread, &thread_ret);
    T(thread_ret != PTHREAD_CANCELED,
      "Thread exit code is not PTHREAD_CANCELED");
  }
  return 0;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    return 1;
  }

  switch (argv[1][0]) {
  default:
    return 1;
  case '1': // pthread-cancel-async-no-cp
    return cancel_async_no_cp();
  case '2': // pthread-cancel-async-in-cp
    return cancel_async_in_cp();
  case '3': // pthread-cancel-deferred-no-cp
    return cancel_deferred_no_cp();
  case '4': // pthread-cancel-deferred-in-cp
    return cancel_deferred_in_cp();
  case '5': // pthread-cancel-async-disabled
    return cancel_async_disabled();
  case '6': // pthread-cancel-deferred-disabled
    return cancel_deferred_disabled();
  case '7': // pthread-cancel-async-masked
    return cancel_async_masked();
  case '8':
    return 0;
  case '9': // pthread-cancel-deferred-in-cp-custom
    return cancel_deferred_in_cp_custom();
  }
}
