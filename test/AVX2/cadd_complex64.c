#include "general.h"

int main(int argc, char const *argv[])
{
  TRINARY_PREAMBLE(SCALE, float);
  CSIMD64(cadd)(z, x, y, c, SCALE);

  for(i=0;i<SCALE;i++)
    ans[i] = x[i] + c * y[i];

  showf(x, SCALE);
  printf("----\n");
  showf(y, SCALE);
  printf("----\n");
  showf(ans, SCALE);
  printf("----\n");
  showf(z, SCALE);
  TRINARY_END;
  return 0;
}