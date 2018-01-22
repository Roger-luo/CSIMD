#include "general.h"

int main(int argc, char const *argv[])
{
  BINARY_PREAMBLE(SCALE, double);
  CSIMD128(divs)(y, x, c, SCALE);

  for(i=0;i<SCALE;i++)
    ans[i] = x[i] / c;

  show(ans, SCALE);
  printf("----\n");
  show(y, SCALE);
  BINARY_END;
  return 0;
}