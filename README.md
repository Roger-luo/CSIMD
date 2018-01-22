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

macro `CSIMD_GENERAL_NAME(PROJECT, TYPE, NAME)` is defined to tweak generated function names. You can use it for your own project name with `PROJECT`. For `CSIMD64` and `CSIMD128` the project name is set to `TH` as default.

## Unit Tests

The unit tests are very simple, it only use CMake's CTest, and there is only a few tests (but I guess it is enough). All the file with extension `.c`: `*.c` under architecture folder in `test` (like `test/AVX`) will be auto-compiled by CTest.

# Acknowledge

All the people contributed to PyTorch SIMD backend for other types.
