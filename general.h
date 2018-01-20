#ifndef SIMD_GENERAL
#define SIMD_GENERAL

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>
#include <complex.h>

#ifndef _MSC_VER
#include <x86intrin.h>
#else
#include <intrin.h>
#endif

#define complex64 float _Complex
#define complex128 double _Complex

#define CONCAT_STRING_2(x,y) CONCAT_STRING_2_EXPAND(x,y)
#define CONCAT_STRING_2_EXPAND(x,y) #x #y

#define CONCAT_STRING_3(x,y,z) CONCAT_STRING_3_EXPAND(x,y,z)
#define CONCAT_STRING_3_EXPAND(x,y,z) #x #y #z

#define CONCAT_STRING_4(x,y,z,w) CONCAT_STRING_4_EXPAND(x,y,z,w)
#define CONCAT_STRING_4_EXPAND(x,y,z,w) #x #y #z #w

#define CONCAT_2(x,y) CONCAT_2_EXPAND(x,y)
#define CONCAT_2_EXPAND(x,y) x ## y

#define CONCAT_3(x,y,z) CONCAT_3_EXPAND(x,y,z)
#define CONCAT_3_EXPAND(x,y,z) x ## y ## z

#define CONCAT_4_EXPAND(x,y,z,w) x ## y ## z ## w
#define CONCAT_4(x,y,z,w) CONCAT_4_EXPAND(x,y,z,w)

#define CSIMD_GENERAL_NAME(PROJECT, TYPE, NAME) \
    CONCAT_4(PROJECT, TYPE, Vector_, NAME)
#endif