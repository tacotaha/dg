#include <stdint.h>
#include <stdio.h>

#include "../normal.h"

#define N 5000000

#define BW 1
#define BINS 50
#define BIN_MIN (-24)

/* critical values:
 * https://www.itl.nist.gov/div898/handbook/eda/section3/eda3674.htm */

double chisq_gof(double mu, double sigma, int32_t (*sample)(double, double)) {
  int bin, sum = 0, observed[BINS] = {0};
  double x, p = 0, chi = 0, expected[BINS] = {0};

  /* sample distribution */
  for (int i = 0; i < N; ++i) {
    bin = floor((sample(mu, sigma) - BIN_MIN + 0.5) / BW);
    ++observed[bin];
  }

  /* build expected probabilities */
  for (int i = 0; i < BINS; ++i)
    for (int j = 0; j < BW; ++j)
      expected[i] += norm(BIN_MIN + BW * i + j, mu, sigma);

  /* compute goodness of fit */
  for (int i = 0; i < BINS; ++i) {
    sum += observed[i];
    p += expected[i];
    x = observed[i] - N * expected[i];
    chi += (x * x) / (N * expected[i]);
  }

  chi += pow((N - sum) - N * (1 - p), 2) / (N * (1 - p));

  return chi;
}
