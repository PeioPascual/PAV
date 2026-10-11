#include "pav_analysis.h"
#include <math.h>

float compute_power(const float *x, unsigned int N) {
  float sum = 0;
  for (unsigned int i = 0; i < N; i++) {
    sum += x[i] * x[i];
  }
  return 10 * log10(sum / N);
}

float compute_am(const float *x, unsigned int N) {
  float sum = 0;
  for (unsigned int i = 0; i < N; i++) {
    sum += fabsf(x[i]);
  }
  return sum / N;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
  unsigned int count = 0;
  for (unsigned int i = 1; i < N; i++) {
    count += (x[i - 1] * x[i] < 0);
  }
  return count * fm / (2 * (N - 1));
}
