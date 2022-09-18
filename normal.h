#ifndef NORMAL_H
#define NORMAL_H

#include <math.h>

/* approximates the normal CDF */
static inline double normcdf(double x, double mu, double sigma) {
  return (1.0 + erf((x - mu) / (sigma * sqrt(2)))) / 2;
}

/* approximates the normal PDF */
static inline double norm(double x, double mu, double sigma) {
  mu = (x - mu) / sigma;
  return exp(-mu * mu * 0.5) / (sigma * sqrt(2.0 * M_PI));
}

/* discrete normal probability */
static inline double dnorm(int x, double mu, double sigma) {
  mu = ((double)x - (mu - (int)mu));
  return exp(-mu * mu / (2.0 * sigma * sigma));
}

#endif /* NORMAL_H */
