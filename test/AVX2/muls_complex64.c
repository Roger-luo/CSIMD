#include <AVX2.h>
#include <complex.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  int n = 4;
  float _Complex *x = (float _Complex *)malloc(n * sizeof(float _Complex));
  float _Complex *y = (float _Complex *)malloc(n * sizeof(float _Complex));
  float _Complex *ans = (float _Complex *)malloc(n * sizeof(float _Complex));
  float _Complex c = 2.0f + 3.0f * I;

  int i, j;
  for(i=0;i<n;i++)
    x[i] = i + (i + 1) * I;

  for(i=0;i<n;i++)
    ans[i] = x[i] * c;

  THZFloatVector_muls_AVX2(y, x, c, n);
  for(i=0;i<n;i++)
  {
    if(cabs(y[i] - ans[i]) > 1e-3) exit(1);
    printf("%f+%fim\n", crealf(y[i]), cimagf(y[i]));
  }

  free(x); free(y); free(ans);
  return 0;
}