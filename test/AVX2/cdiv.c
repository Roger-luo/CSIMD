#include "general.h"

int main(int argc, char const *argv[])
{
  TRINARY_OPERATION(
    SCALE, float, x[i] / y[i],
    CSIMD64(cdiv)(z, x, y, SCALE), 1e-5);

  TRINARY_OPERATION(
    SCALE, double, x[i] / y[i],
    CSIMD128(cdiv)(z, x, y, SCALE), 1e-10);
  return 0;
}