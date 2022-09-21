#include <assert.h>
#include <stdint.h>
#include <time.h>

#define N 5000000

double bench(double mu, double sigma, int32_t (*sample)(double, double)) {
  double delta;
  struct timespec start, stop;

  assert(!clock_gettime(CLOCK_REALTIME, &start));

  for (int i = 0; i < N; ++i) sample(mu, sigma);

  assert(!clock_gettime(CLOCK_REALTIME, &stop));

  delta = (double)(stop.tv_sec - start.tv_sec) +
          1.0e-9 * (double)(stop.tv_nsec - start.tv_nsec);

  /* samples per sec. */
  return (double)N / delta;
}
