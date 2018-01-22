#include "general.h"

int main(int argc, char const *argv[])
{
  // TRINARY_OPERATION(
  //   SCALE, float, x[i] + c * y[i],
  //   CSIMD64(cadd)(z, x, y, c, SCALE), 1e-10);

  TRINARY_OPERATION(
    SCALE, double, x[i] + c * y[i],
    CSIMD128(cadd)(z, x, y, c, SCALE), 1e-10);
  return 0;
}