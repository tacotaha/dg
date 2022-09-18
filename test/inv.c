#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//#define CSPRNG

#include "../sample_inv.h"

extern double chisq_gof(double, double, int32_t (*sample)(double, double));

int main() {
  // srand(time(0));

  double l, r;
  double mu[] = {0, 0.5, 1.2, 1.67};
  double sigma[] = {4.1, 5.33, 5.67, 6.2};

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
