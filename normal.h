#ifndef NORMAL_H
#define NORMAL_H

#include <math.h>

/* coefficients of rational approximations */
#define A0 (-3.969683028665376e+01)
#define A1 (2.209460984245205e+02)
#define A2 (-2.759285104469687e+02)
#define A3 (1.383577518672690e+02)
#define A4 (-3.066479806614716e+01)
#define A5 2.506628277459239e+00
#define B0 (-5.447609879822406e+01)
#define B1 (1.615858368580409e+02)
#define B2 (-1.556989798598866e+02)
#define B3 6.680131188771972e+01
#define B4 (-1.328068155288572e+01)
#define C0 (-7.784894002430293e-03)
#define C1 (-3.223964580411365e-01)
#define C2 (-2.400758277161838e+00)
#define C3 (-2.549732539343734e+00)
#define C4 (4.374664141464968e+00)
#define C5 (2.938163982698783e+00)
#define D0 (7.784695709041462e-03)
#define D1 (3.224671290700398e-01)
#define D2 (2.445134137142996e+00)
#define D3 (3.754408661907416e+00)

/* define break points */
#define P_LOW (0.02425)
#define P_HIGH (1 - P_LOW)

/* approximates the normal CDF */
static inline long double invnorm(long double p) {
  long double q, r;

  if (p < P_LOW) {
    /* Rational approximation for lower region */
    q = sqrt(-2 * log(p));
    return (((((C0 * q + C1) * q + C2) * q + C3) * q + C4) * q + C5) /
           ((((D0 * q + D1) * q + D2) * q + D3) * q + 1);
  } else if (p > P_HIGH) {
    /* Rational approximation for upper region */
    q = sqrt(-2 * log(1 - p));
    return -(((((C0 * q + C1) * q + C2) * q + C3) * q + C4) * q + C5) /
           ((((D0 * q + D1) * q + D2) * q + D3) * q + 1);
  } else {
    /* Rational approximation for central region */
    q = p - 0.5;
    r = q * q;
    return (((((A0 * r + A1) * r + A2) * r + A3) * r + A4) * r + A5) * q /
           (((((B0 * r + B1) * r + B2) * r + B3) * r + B4) * r + 1);
  }
}

/* approximates the normal PDF */
static inline double norm(double x, double mu, double sigma) {
  mu = (x - mu) / sigma;
  return exp(-mu * mu * 0.5) / (sigma * sqrt(2 * M_PI));
}

#endif /* NORMAL_H */
