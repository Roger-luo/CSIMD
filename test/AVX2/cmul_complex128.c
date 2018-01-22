#include <stdlib.h>
#include <AVX2.h>
#include <complex.h>

int main(int argc, char const *argv[])
{
  int n = 4;
  double _Complex *x = (double _Complex *)malloc(n * sizeof(double _Complex));
  double _Complex *y = (double _Complex *)malloc(n * sizeof(double _Complex));
  double _Complex *z = (double _Complex *)malloc(n * sizeof(double _Complex));
  double _Complex *ans = (double _Complex *)malloc(n * sizeof(double _Complex));

  int i, j;
  for(i=0;i<n;i++)
    x[i] = i + (i + 1) * I;

  for(i=0, j=n;i<n;i++,j--)
    y[i] = j + (j - 1) * I;

  for(i=0;i<n;i++)
    ans[i] = x[i] * y[i];

  THZDoubleVector_cmul_AVX2(z, x, y, n);

  for(i=0;i<n;i++)
    if(cabs(z[i] - ans[i]) > 1e-10) exit(1);

  free(x); free(y); free(z); free(ans);
  return 0;
}