#include "general.h"

int main(int argc, char const *argv[])
{
  BINARY_OPERATION(
      SCALE, float, x[i] / c,
      CSIMD64(divs)(y, x, c, SCALE), 1e-5);

  BINARY_OPERATION(
    SCALE, double, x[i] / c,
    CSIMD128(divs)(y, x, c, SCALE), 1e-10);
  return 0;
}