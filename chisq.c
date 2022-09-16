// gcc chisq.c -lm

#include <stdio.h>
#include <time.h>

#include "karney.h"
#include "normal.h"

#define N 5000000

#define BW 1
#define BINS 50
#define BIN_MIN (-24)

#define SIGMA 6
#define MU 0

int main() {
  // srand(time(0));
  int sum = 0, freq[BINS] = {0};
  double x, p = 0, chi = 0, expected[BINS] = {0};

  /* sample distribution */
  for (int i = 0; i < N; ++i) {
    int bin = floor((sample_karney(MU, SIGMA) - BIN_MIN + 0.5) / BW);
    ++freq[bin];
  }

  /* build expected probabilities */
  for (int i = 0; i < BINS; ++i)
    for (int j = 0; j < BW; ++j)
      expected[i] += norm(BIN_MIN + BW * i + j, MU, SIGMA);

  /* compute goodness of fit */
  for (int i = 0; i < BINS; ++i) {
    sum += freq[i];
    p += expected[i];
    x = freq[i] - N * expected[i];
    chi += (x * x) / (N * expected[i]);
  }

  chi += pow((N - sum) - N * (1 - p), 2) / (N * (1 - p));

  printf("%lf\n", chi);

  return 0;
}
