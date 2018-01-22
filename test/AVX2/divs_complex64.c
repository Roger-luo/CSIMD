#include "general.h"

int main(int argc, char const *argv[])
{
  BINARY_PREAMBLE(SCALE, float);
  CSIMD64(divs)(y, x, c, SCALE);

  for(i=0;i<SCALE;i++)
    ans[i] = x[i] / c;

  showf(ans, SCALE);
  printf("----\n");
  showf(y, SCALE);
  BINARY_END;
  return 0;
}