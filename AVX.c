#include "AVX.h"

void CSIMD128(copy)(complex128 *y, const complex128 *x, const ptrdiff_t n) {
  ptrdiff_t i;
  ptrdiff_t off;

  double *my = (double *)y;
  double *mx = (double *)x;
  ptrdiff_t mn = 2 * n;

  for(i=0;i<=((mn)-8);i+=8) {
    _mm256_storeu_pd(my+i, _mm256_loadu_pd(mx+i));
    _mm256_storeu_pd(my+i+4, _mm256_loadu_pd(mx+i+4));
  }
  off = (mn) - ((mn)%8);
  for(i=0; i<((n)%8); i++) {
    y[off+i] = x[off+i];
  }
}

void CSIMD64(copy)(complex64 *y, const complex64 *x, const ptrdiff_t n) {
  ptrdiff_t i;
  ptrdiff_t off;

  float *my = (float *)y;
  float *mx = (float *)x;
  ptrdiff_t mn = 2 * n;

  for (i=0; i<=((mn)-16); i+=16) {
    _mm256_storeu_ps(my+i, _mm256_loadu_ps(mx+i));
    _mm256_storeu_ps(my+i+8, _mm256_loadu_ps(mx+i+8));
  }
  off = (mn) - ((mn)%16);
  for (i=0; i<((mn)%16); i++) {
    y[off+i] = x[off+i];
  }
}

void CSIMD128(fill)(complex128 *z, const complex128 c, const ptrdiff_t n) {
  ptrdiff_t i;
  ptrdiff_t off;
  double *x = (double *)z;
  ptrdiff_t len = 2 * n;
  __m256d YMM0 = _mm256_set_pd(
    cimag(c), creal(c), cimag(c), creal(c));
  for(i=0;i<=((len)-16); i+=16) {
    _mm256_storeu_pd((x)+i, YMM0);
    _mm256_storeu_pd((x)+i+4, YMM0);
    _mm256_storeu_pd((x)+i+8, YMM0);
    _mm256_storeu_pd((x)+i+12, YMM0);
  }
  off = (len) - ((len)%16);
  for(i=0; i<((len)&16); i++) {
    x[off+i] = c;
  }
}

void CSIMD64(fill)(complex64 *z, const complex64 c, const ptrdiff_t n) {
  ptrdiff_t i;
  ptrdiff_t off;
  __m256 YMM0 = _mm256_set_ps(
                  cimag(c), creal(c),
                  cimag(c), creal(c),
                  cimag(c), creal(c),
                  cimag(c), creal(c));
  float *x = (float *)z;
  ptrdiff_t len = 2 * n;

  for (i=0; i<=((len)-32); i+=32) {
    _mm256_storeu_ps((x)+i  , YMM0);
    _mm256_storeu_ps((x)+i+8, YMM0);
    _mm256_storeu_ps((x)+i+16, YMM0);
    _mm256_storeu_ps((x)+i+24, YMM0);
  }
  off = (len) - ((len)%32);
  for (i=0; i<((len)%32); i++) {
    x[off+i] = c;
  }
}

void CSIMD128(adds)(complex128 *y, const complex128 *x, const complex128 c, const ptrdiff_t n) {
  ptrdiff_t i, off;
  ptrdiff_t len = 2 * n;

  double *mx = (double *)x;
  double *my = (double *)y;
  __m256d YMM15 = COMPLEX128_TO_M256D(creal(c), cimag(c));
  __m256d YMM0, YMM1;
  for(i=0;i<=((len)-8);i+=8) {
    YMM0 = _mm256_loadu_pd(mx+i);
    YMM1 = _mm256_loadu_pd(mx+i+4);
    YMM0 = _mm256_add_pd(YMM0, YMM15);
    YMM1 = _mm256_add_pd(YMM1, YMM15);
    _mm256_storeu_pd(my+i, YMM0);
    _mm256_storeu_pd(my+i+4, YMM1);
  }
  off = (n) - ((n)%4);
  for (i=0; i<((n)%4); i++) {
    y[off+i] = x[off+i] + c;
  }
}

void CSIMD64(adds)(complex64 *y, const complex64 *x, const complex64 c, const ptrdiff_t n) {
  ptrdiff_t i, off;
  ptrdiff_t len = 2 * n;

  float *mx = (float *)x;
  float *my = (float *)y;
  __m256 YMM15 = COMPLEX64_TO_M256(crealf(c), cimagf(c));
  __m256 YMM0, YMM1;
  for(i=0;i<=((len)-16);i+=16) {
    YMM0 = _mm256_loadu_ps(mx+i);
    YMM1 = _mm256_loadu_ps(mx+i+8);
    YMM0 = _mm256_add_ps(YMM0, YMM15);
    YMM1 = _mm256_add_ps(YMM1, YMM15);
    _mm256_storeu_ps(my+i, YMM0);
    _mm256_storeu_ps(my+i+8, YMM1);
  }
  off = (n) - ((n)%8);
  for (i=0; i<((n)%8); i++) {
    y[off+i] = x[off+i] + c;
  }
}