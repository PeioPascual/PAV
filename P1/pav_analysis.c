#include "pav_analysis.h"
#include <math.h>

float compute_power(const float *x, unsigned int N) {
  float sum = 0;
  for (unsigned int i = 0; i < N; i++) {
    sum += x[i] * x[i];
  }
  return 10 * log10(sum / N);
}

void compute_power_hamming(unsigned int len, float *hamming_pow, const float *x, unsigned int N, unsigned int M) {
  float sumx, sumw = 0, xw;
  float w[N];

  for (unsigned int n = 0; n < N; n++) {
    w[n] = 0.54 - 0.46 * cosf(2 * M_PI * n / (N - 1));
    sumw += w[n] * w[n];
  }

  for (unsigned int i = 0; i < len; i++) {
    sumx = 0;

    for (unsigned int n = 0; n < N; n++) {
      xw = x[i * M + n] * w[n];
      sumx += xw * xw;
    }

    hamming_pow[i] = 10 * log10(sumx / sumw);
  }
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
