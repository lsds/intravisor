#include <regex.h>
#include <fnmatch.h>
#include <glob.h>
#include <stdio.h>

int test_fnmatch();
int test_glob();
int test_regcomp();

int main(int argc, char **argv) {
  if (argc < 2) return -1;

  switch (argv[1][0]) {
    case '0':
      return test_fnmatch();
    case '1':
      return test_glob();
    case '2':
      return test_regcomp();
  }

  return -1;
}

int test_fnmatch() {
  const char *teststr = "dog123123cat";

  if (fnmatch("*cat*", teststr, 0)) return 1;
  if (!fnmatch("*bird*", teststr, 0)) return 2;

  return 0;
}

// TODO: malloc usage in this currently throws a capability fault
int test_glob() {
  glob_t globbuf;
  glob("/proc/self/s*", GLOB_ERR, NULL, &globbuf);

  for (int i = 0; i < globbuf.gl_pathc; i++) {
      printf("%s\n", globbuf.gl_pathv[i]);
  }

  globfree(&globbuf);

  return 0;
}

int test_regcomp() {
  regex_t preg;
  if (regcomp(&preg, "dog[1-3]+cat", REG_EXTENDED)) return 1;

  if (regexec(&preg, "dog123123cat", 0, NULL, 0)) return 2;

  int ret;
  if (!(ret = regexec(&preg, "dog456456cat", 0, NULL, 0))) return 3;

  char errbuf[256];
  if (!regerror(ret, &preg, errbuf, 256)) return 4;

  printf("errbuff: %s\n", errbuf);

  return 0;
}
