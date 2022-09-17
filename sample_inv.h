#ifndef SAMPLE_INV_H
#define SAMPLE_INV_H

#include <assert.h>

#include "entropy.h"
#include "normal.h"

#define TAIL_CUT 12

static int __invtab_m;
static double *__invtab;

/* build the inversion table */
static inline void inv_init(double mu, double sigma) {
  __invtab_m = ceil(TAIL_CUT * sigma);

  if (mu == 0) {
    /* compressed table */
    assert((__invtab = calloc(1, sizeof(double) * __invtab_m)));
    __invtab[0] = 0.5;
    for (int i = 1; i < __invtab_m; ++i) __invtab[i] = dnorm(i, mu, sigma);
  } else {
    assert((__invtab = calloc(1, sizeof(double) * ((__invtab_m << 1) + 1))));
    for (int i = 0; i < __invtab_m; ++i) {
      __invtab[__invtab_m - i - 1] = dnorm(-i, mu, sigma);
      __invtab[__invtab_m + i - 1] = dnorm(i, mu, sigma);
    }
  }
}

/* free the inversion table */
static inline void inv_free() {
  free(__invtab);
  __invtab_m = 0;
}

static inline int32_t sample(double mu, double sigma) {
  int32_t result;
  if (mu == 0) {
    while (uniformr() >= __invtab[(result = uniform32() % __invtab_m)]);
    return uniformb() ? -result : result;
  }
  while (uniformr() >= __invtab[(result = uniform32() % (((__invtab_m << 1) + 1)))]);
  return result + (int)mu - __invtab_m + 1;
}

#endif /* SAMPLE_INV_H */
