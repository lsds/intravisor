#define _GNU_SOURCE

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

/*
 * Naive test simply generates SAMPLE_SIZE random numbers for each function
 * and checks bounds on each generated number.
 */

#define SAMPLE_SIZE 1000

unsigned short xi[3] = {
  1, 2, 3
};

int test_seeds() {
  srand(1);
  srand48(2);
  seed48(xi);

  // default values of a, b copied from musl
  unsigned short lcong_params[7] = {
    1, 2, 3, // Xi
    0xe66d, 0xdeec, 0x5, // a
    0xb // b
  };
  lcong48(lcong_params);

  return 0;
}

int test_rand() {
  for (int i = 1; i < SAMPLE_SIZE; i++) {
    int num = rand();

    if (num < 0 || num > RAND_MAX) {
      return 1;
    }
  }

  return 0;
}

int test_drand48_erand48() {
  for (int i = 1; i < SAMPLE_SIZE; i++) {
    double numd = drand48();
    double nume = erand48(xi);

    if (numd < 0.0 || nume < 0.0 || numd > 1.0 || nume > 1.0) {
      return 2;
    }
  }

  return 0;
}

int test_lrand48_nrand48() {
  const long LRAND_MAX  = 1l << 31;

  for (int i = 1; i < SAMPLE_SIZE; i++) {
    long numl = lrand48();
    long numn = nrand48(xi);

    if (numl < 0 || numn < 0 || numl > LRAND_MAX || numn > LRAND_MAX) {
      return 3;
    }
  }

  return 0;
}

int test_mrand48_jrand48() {
  const long MRAND_MAX = 1l << 31;
  const long MRAND_MIN = -(1l << 31);

  for (int i = 1; i < SAMPLE_SIZE; i++) {
    long numm = mrand48();
    long numj = jrand48(xi);

    if (numm < MRAND_MIN || numj < MRAND_MIN || numm > MRAND_MAX || numj > MRAND_MAX) {
      return 4;
    }
  }

  return 0;
}

int main(int argc, char **argv) {

  switch (argv[1][0]) {
    case '0': // prng-seeds
      return test_seeds();

    case '1': // prng-rand
      return test_rand();

    case '2': // prng-drand48-erand48
      return test_drand48_erand48();

    case '3': // prng-lrand48-nrand48
      return test_lrand48_nrand48();

    case '4': // prng-mrand48-jrand48
      return test_mrand48_jrand48();
  }

  return -1;
}
