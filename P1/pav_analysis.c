#include "pav_analysis.h"
#include <math.h>

float compute_power(const float *x, unsigned int N) {
  float sum = 0;
  for (int i = 0; i < N; i++) {
    sum += pow(fabs(x[i]), 2);
  }
  return sum / N;
}

float compute_am(const float *x, unsigned int N) {
  float sum = 0;
  for (int i = 0; i < N; i++) {
    sum += fabs(x[i]);
  }
  return sum / N;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
  float count = 0;
  for (int i = 0; i < N - 1; i++) {
    count += (x[i] * x[i + 1] < 0);
  }
  return count * fm / (N - 1);
}
