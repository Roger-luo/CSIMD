#ifndef SIMD_AVX
#define SIMD_AVX

#include "general.h"

#ifdef CSIMD128
#undef CSIMD128
#endif

#ifdef CSIMD64
#undef CSIMD64
#endif

#define CSIMD128(NAME) \
    CSIMD_GENERAL_NAME(TH, ZDouble, NAME##_AVX)

#define CSIMD64(NAME) \
    CSIMD_GENERAL_NAME(TH, ZFloat, NAME##_AVX)

extern void CSIMD128(copy)(complex128 *y, const complex128 *x, const ptrdiff_t n);
extern void CSIMD128(fill)(complex128 *z, const complex128 c, const ptrdiff_t n);

extern void CSIMD64(copy)(complex64 *y, const complex64 *x, const ptrdiff_t n);
extern void CSIMD64(fill)(complex64 *z, const complex64 c, const ptrdiff_t n);

#endif
