#ifndef ENTROPY_H
#define ENTROPY_H

#include <stdint.h>
#include <stdlib.h>

#define CSPRNG 1

#if CSPRNG

#include <float.h>
#include <sys/random.h>

static inline size_t rng(void* buffer, size_t len) {
  return getrandom(buffer, len, GRND_RANDOM);
}

static inline uint32_t uniform32() {
  uint32_t r;
  rng(&r, sizeof(uint32_t));
  return r;
}

static inline double uniformr() {
  uint32_t r = uniform32();
  return ldexpf(r & ((1 << FLT_MANT_DIG) - 1), -FLT_MANT_DIG);
}

#else

static inline uint32_t uniform32() { return (uint32_t)random(); }

static inline double uniformr() { return drand48(); }

#endif

static inline unsigned long uniformb() { return uniform32() & 1; }

#endif /* ENTROPY_H */
