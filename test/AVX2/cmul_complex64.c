#include <AVX2.h>
#include <complex.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  int n = 4;
  float _Complex *x = (float _Complex *)malloc(n * sizeof(float _Complex));
  float _Complex *y = (float _Complex *)malloc(n * sizeof(float _Complex));
  float _Complex *z = (float _Complex *)malloc(n * sizeof(float _Complex));
  float _Complex *ans = (float _Complex *)malloc(n * sizeof(float _Complex));

  int i, j;
  for(i=0;i<n;i++)
    x[i] = i + (i + 1) * I;

  for(i=0, j=n;i<n;i++,j--)
    y[i] = j + (j - 1) * I;

  for(i=0;i<n;i++)
    ans[i] = x[i] * y[i];

  THZFloatVector_cmul_AVX2(z, x, y, n);
  for(i=0;i<n;i++)
    if(cabs(z[i] - ans[i]) > 1e-3) exit(1);

  free(x); free(y); free(z); free(ans);
  return 0;
}