#ifndef CSIMD_TEST_UTILS
#define CSIMD_TEST_UTILS

#include <stdio.h>
#include <complex.h>

#define ASSERT_EQ(A, B, EPS) \
  if(cabs(A - B) > EPS) { \
    printf("Expect %f+%fim, got %f+%fim\n", \
      creal(A), cimag(A), creal(B), cimag(B)); \
    printf("norm diff: %lf\n", cabs(A - B)); \
    exit(1); \
  }

#define MAKE_ARRAY(NAME, N, TYPE) \
  TYPE *NAME = (TYPE *)malloc(N * sizeof(TYPE))

#define BINARY_PREAMBLE(N, TYPE) \
  MAKE_ARRAY(x, N, TYPE _Complex); \
  MAKE_ARRAY(y, N, TYPE _Complex); \
  MAKE_ARRAY(ans, N, TYPE _Complex); \
  TYPE _Complex c = 2.0f + 3.0f * I; \
  int i, j; \
  for(i=0;i<N;i++) \
    x[i] = i + (i+1) * I

#define TRINARY_PREAMBLE(N, TYPE) \
  MAKE_ARRAY(x, N, TYPE _Complex); \
  MAKE_ARRAY(y, N, TYPE _Complex); \
  MAKE_ARRAY(z, N, TYPE _Complex); \
  MAKE_ARRAY(ans, N, TYPE _Complex); \
  TYPE _Complex c = 2.0f + 3.0f * I; \
  int i, j; \
  for(i=0;i<N;i++) \
    x[i] = i + (i+1) * I; \
  for(i=0, j=N;i<N;i++,j--) \
    y[i] = j + (j-1) * I

#define BINARY_END \
  free(x); free(y); free(ans)

#define TRINARY_END \
  free(x); free(y); free(z); free(ans)

#define BINARY_OPERATION(N, TYPE, CODE, SIMD, EPS) \
{ \
  BINARY_PREAMBLE(N, TYPE); \
\
  for(i=0;i<N;i++) \
  { \
    ans[i] = CODE; \
  } \
\
  SIMD; \
\
  for(i=0;i<N;i++) \
    ASSERT_EQ(y[i], ans[i], EPS); \
  BINARY_END;\
}

#define TRINARY_OPERATION(N, TYPE, CODE, SIMD, EPS) \
{ \
  TRINARY_PREAMBLE(N, TYPE); \
\
  for(i=0;i<N;i++) \
  { \
    ans[i] = CODE; \
  } \
\
  SIMD; \
\
  for(i=0;i<N;i++) \
    ASSERT_EQ(z[i], ans[i], EPS); \
  TRINARY_END; \
}


void show(double _Complex *x, int n) {
  int i;
  for(i=0;i<n;i++) {
    printf("%lf+%lfim\n", creal(x[i]), cimag(x[i]));
  }
}

void showf(float _Complex *x, int n) {
  int i;
  for(i=0;i<n;i++) {
    printf("%f+%fim\n", crealf(x[i]), cimagf(x[i]));
  }
}

#endif