#include <AVX2.h>
#include <complex.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
  int n = 4;
  double _Complex *x = (double _Complex *)malloc(n * sizeof(double _Complex));
  double _Complex *y = (double _Complex *)malloc(n * sizeof(double _Complex));
  double _Complex *ans = (double _Complex *)malloc(n * sizeof(double _Complex));
  double _Complex c = 2.0 + 3.0 * I;

  int i, j;
  for(i=0;i<n;i++)
    x[i] = i + (i + 1) * I;

  for(i=0;i<n;i++)
    ans[i] = x[i] * c;

  THZDoubleVector_muls_AVX2(y, x, c, n);
  for(i=0;i<n;i++)
    if(cabs(y[i] - ans[i]) > 1e-10) exit(1);

  free(x); free(y); free(ans);
  return 0;
}