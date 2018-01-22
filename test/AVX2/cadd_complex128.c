#include "general.h"

int main(int argc, char const *argv[])
{
  TRINARY_PREAMBLE(SCALE, double);
  CSIMD128(cadd)(z, x, y, c, SCALE);

  for(i=0;i<SCALE;i++)
    ans[i] = x[i] + c * y[i];

  show(x, SCALE);
  printf("----\n");
  show(y, SCALE);
  printf("----\n");
  show(ans, SCALE);
  printf("----\n");
  show(z, SCALE);
  TRINARY_END;
  return 0;
}