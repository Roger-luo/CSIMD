#ifndef SIMD_AVX2
#define SIMD_AVX2

#include "general.h"

#ifdef CSIMD128
#undef CSIMD128
#endif

#ifdef CSIMD64
#undef CSIMD64
#endif

#define CSIMD128(NAME) \
    CSIMD_GENERAL_NAME(TH, ZDouble, NAME##_AVX2)

#define CSIMD64(NAME) \
    CSIMD_GENERAL_NAME(TH, ZFloat, NAME##_AVX2)

extern void CSIMD128(cdiv)(complex128 *z, const complex128 *x, const complex128 *y, const ptrdiff_t n);
extern void CSIMD128(divs)(complex128 *y, const complex128 *x, const complex128 c, const ptrdiff_t n);
extern void CSIMD128(cmul)(complex128 *z, const complex128 *x, const complex128 *y, const ptrdiff_t n);
extern void CSIMD128(muls)(complex128 *y, const complex128 *x, const complex128 c, const ptrdiff_t n);
extern void CSIMD128(cadd)(complex128 *z, const complex128 *x, const complex128 *y, const complex128 c, const ptrdiff_t n);

extern void CSIMD64(cdiv)(complex64 *z, const complex64 *x, const complex64 *y, const ptrdiff_t n);
extern void CSIMD64(divs)(complex64 *y, const complex64 *x, const complex64 c, const ptrdiff_t n);
extern void CSIMD64(cmul)(complex64 *z, const complex64 *x, const complex64 *y, const ptrdiff_t n);
extern void CSIMD64(muls)(complex64 *y, const complex64 *x, const complex64 c, const ptrdiff_t n);
extern void CSIMD64(cadd)(complex64 *z, const complex64 *x, const complex64 *y, const complex64 c, const ptrdiff_t n);

#endif
