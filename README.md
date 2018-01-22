# CSIMD
SIMD Accelerated Operations for Complex Numbers.

# Goal
This project aims to provide PyTorch's CPU backend with SIMD support for complex operations.

following operations is implemented:

## AVX
- [x] copy
- [x] fill

## AVX2
- [x] cdiv
- [x] divs
- [x] cmul
- [x] muls
- [x] cadd
- [x] adds

# Definitions

## Macros

This package provides two macros: `CSIMD64` and `CSIMD128` for `float _Complex` (`complex64`) and `double _Complex` (`complex128`). By default the CSIMD macro will be expanded to match SIMD functions defined in PyTorch, e.g

with `AVX2.h` included, `CSIMD64(divs)` will be expanded to `THZFloatVector_divs_AVX2`.

## Unit Tests

The unit tests are very simple, it only use CMake's CTest, and there is only a few tests (but I guess it is enough).

# Acknowledge

All the people contributed to PyTorch SIMD backend for other types.
