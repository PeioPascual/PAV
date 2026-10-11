#ifndef PAV_ANALYSIS_H
#define PAV_ANALYSIS_H

float compute_power(const float *x, unsigned int N);
void compute_power_hamming(unsigned int len, float *hamming_pow, const float *x, unsigned int N, unsigned int M);
float compute_am(const float *x, unsigned int N);
float compute_zcr(const float *x, unsigned int N, float fm);

#endif	/* PAV_ANALYSIS_H	*/
