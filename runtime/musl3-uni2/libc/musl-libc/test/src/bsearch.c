#include <stdlib.h>

typedef struct elem {
  int k;
  char v;
} elem;

int cmp(const void *pkey, const void *pelem) {
  return *(int *)pkey - ((elem *)pelem)->k;
}

int main(int argc, char **argv) {
  elem arr[] = {{1, 'd'},  {2, 'x'},  {5, 'e'},  {8, 'd'},
                {14, 'j'}, {15, 'b'}, {30, 'l'}, {30, 'a'}};
  int k;
  void *res;

  switch (argv[1][0]) {

  case '0':
    k = 14;
    res = bsearch(&k, arr, 8, sizeof(elem), cmp);

    if (__builtin_cheri_tag_get(res) != __builtin_cheri_tag_get(arr)) {
      return 1;
    }
    if (__builtin_cheri_length_get(res) != sizeof(arr)) {
      return 2;
    }
    if (((elem *)res)->v != 'j') {
      return 3;
    }
    return 0;

  case '1':
    k = 30;
    res = bsearch(&k, arr, 8, sizeof(elem), cmp);
    char v = ((elem *)res)->v;
    if (v != 'l' && v != 'a') {
      return 1;
    }
    return 0;

  case '2':
    k = 11;
    res = bsearch(&k, arr, 8, sizeof(elem), cmp);
    if (__builtin_cheri_tag_get(res)) {
      return 1;
    }
    if (res) {
      return 2;
    }
    return 0;

  default:
    return 1;
  }
}
