#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define CSPRNG

#include "../sample_inv.h"

extern double chisq_gof(double, double, int32_t (*sample)(double, double));
extern double bench(double, double, int32_t (*sample)(double, double));

int main() {
  // srand(time(0));

  double l, r, s, ep = 100.0 / 3 - 10;
  double mu[] = {0, 0.5, 1.2, 1.67};
  double sigma[] = {4.1, 5.33, 5.67, 6.2};

  printf("Running benchmarks...\n");
  for (double sigma = 10; sigma < 200; sigma += ep) {
    inv_init(0, sigma);
    s = bench(0, sigma, sample);
    inv_free();
    printf("%lf\t%lf\n", sigma, s * 1e-6);
  }

  printf("\nChecking chi-squared statistic...\n");
  for (int j = 0; j < (1 << 3); ++j)
    for (int i = 0; i < sizeof(mu) / sizeof(mu[0]); ++i) {
      inv_init(-mu[i], sigma[i]);
      l = chisq_gof(-mu[i], sigma[i], sample);
      inv_free();

      inv_init(mu[i], sigma[i]);
      r = chisq_gof(mu[i], sigma[i], sample);
      inv_free();
      printf("%lf %lf %lf %lf\n", mu[i], sigma[i], l, r);
    }

  return 0;
}
