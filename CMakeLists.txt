cmake_minimum_required(VERSION 2.6)

IF(POLICY CMP0026)
  CMAKE_POLICY(SET CMP0026 OLD)
ENDIF()

SET(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
SET(CMAKE_LIBRARY_PATH /usr/lib/x86_64-linux-gnu/ ${CMAKE_LIBRARY_PATH})

IF(MSVC)
  # MSVC now supports C99 since VS2013/VS2015, however the standard version switch is not provided yet
  # SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /std:c99")
ELSE(MSVC)
  # enable gnu99 and not c99 because we use
  # gnu extensions like posix_memalign
  SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
ENDIF(MSVC)

IF(MSVC)
  ADD_DEFINITIONS(-D_CRT_SECURE_NO_DEPRECATE=1)  # respect the standard
ENDIF(MSVC)

IF(UNIX)
  # prevent Unknown CMake command "check_function_exists".
  INCLUDE(CheckFunctionExists)
ENDIF(UNIX)

# ARM specific flags
FIND_PACKAGE(ARM)
IF (ASIMD_FOUND)
  MESSAGE(STATUS "asimd/Neon found with compiler flag : -D__NEON__")
  SET(CMAKE_C_FLAGS "-D__NEON__ ${CMAKE_C_FLAGS}")
ELSEIF (NEON_FOUND)
  MESSAGE(STATUS "Neon found with compiler flag : -mfpu=neon -D__NEON__")
  SET(CMAKE_C_FLAGS "-mfpu=neon -D__NEON__ ${CMAKE_C_FLAGS}")
ENDIF (ASIMD_FOUND)
IF (CORTEXA8_FOUND)
  MESSAGE(STATUS "Cortex-A8 Found with compiler flag : -mcpu=cortex-a8")
  SET(CMAKE_C_FLAGS "-mcpu=cortex-a8 -fprefetch-loop-arrays ${CMAKE_C_FLAGS}")
ENDIF (CORTEXA8_FOUND)
IF (CORTEXA9_FOUND)
  MESSAGE(STATUS "Cortex-A9 Found with compiler flag : -mcpu=cortex-a9")
  SET(CMAKE_C_FLAGS "-mcpu=cortex-a9 ${CMAKE_C_FLAGS}")
ENDIF (CORTEXA9_FOUND)

FIND_PACKAGE(SSE) # checks SSE, AVX and AVX2
IF(C_SSE2_FOUND)
  MESSAGE(STATUS "SSE2 Found")
  SET(CMAKE_C_FLAGS "${C_SSE2_FLAGS} -DUSE_SSE2 ${CMAKE_C_FLAGS}")
ENDIF(C_SSE2_FOUND)
IF(C_SSE3_FOUND)
  MESSAGE(STATUS "SSE3 Found")
  SET(CMAKE_C_FLAGS "${C_SSE3_FLAGS} -DUSE_SSE3 ${CMAKE_C_FLAGS}")
ENDIF(C_SSE3_FOUND)
# we don't set -mavx and -mavx2 flags globally, but only for specific files
# however, we want to enable the AVX codepaths, so we still need to
# add USE_AVX and USE_AVX2 macro defines
IF(C_AVX_FOUND)
  MESSAGE(STATUS "AVX Found")
  SET(CMAKE_C_FLAGS "-DUSE_AVX ${CMAKE_C_FLAGS}")
ENDIF(C_AVX_FOUND)
IF(C_AVX2_FOUND)
  MESSAGE(STATUS "AVX2 Found")
  SET(CMAKE_C_FLAGS "-DUSE_AVX2 ${CMAKE_C_FLAGS}")
ENDIF(C_AVX2_FOUND)

# IF ANY SIMD FOUND
IF(C_AVX2_FOUND OR C_AVX_FOUND OR C_SSE4_2_FOUND OR C_SSE4_1_FOUND)
ENDIF(C_AVX2_FOUND OR C_AVX_FOUND OR C_SSE4_2_FOUND OR C_SSE4_1_FOUND)

# IF SSE4 FOUND
IF(C_SSE4_1_FOUND AND C_SSE4_2_FOUND)
ENDIF(C_SSE4_1_FOUND AND C_SSE4_2_FOUND)

# IF AVX FOUND
IF(C_AVX_FOUND)
  IF(MSVC)
    SET_SOURCE_FILES_PROPERTIES(AVX.c PROPERTIES COMPILE_FLAGS "/Ox /arch:AVX ${C_AVX_FLAGS}")
  ELSE(MSVC)
    SET_SOURCE_FILES_PROPERTIES(AVX.c PROPERTIES COMPILE_FLAGS "-O3 ${C_AVX_FLAGS}")
  ENDIF(MSVC)
  SET(simd ${simd} AVX.c)
ENDIF(C_AVX_FOUND)

IF(C_AVX2_FOUND)
  IF(MSVC)
    SET_SOURCE_FILES_PROPERTIES(AVX2.c PROPERTIES COMPILE_FLAGS "/Ox /arch:AVX2 ${C_AVX2_FLAGS}")
  ELSE(MSVC)
    SET_SOURCE_FILES_PROPERTIES(AVX2.c PROPERTIES COMPILE_FLAGS "-O3 ${C_AVX2_FLAGS}")
  ENDIF(MSVC)
  SET(simd ${simd} AVX2.c)
ENDIF(C_AVX2_FOUND)

SET(hdr AVX.h AVX2.h)
SET(src AVX.c AVX2.c)

SET(src ${src} ${hdr} ${simd})
add_library(csimd SHARED ${src})


MACRO(add_test_case section case)
add_executable("test_${section}_${case}" "test/${section}/${case}.c")
target_link_libraries("test_${section}_${case}" csimd m)
add_test("${section}_${case}" "test_${section}_${case}")
ENDMACRO()

# get subdirectories.
# https://stackoverflow.com/questions/
# 7787823/cmake-how-to-get-the-name-of-
# all-subdirectories-of-a-directory

MACRO(SUBDIRLIST result curdir)
  FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${curdir}/${child})
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

include(CTest)
enable_testing()
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

SUBDIRLIST(ALL_TEST_SECTIONS ${CMAKE_CURRENT_SOURCE_DIR}/test)

FOREACH(section ${ALL_TEST_SECTIONS})
  file(GLOB TEST_CASES "${CMAKE_CURRENT_SOURCE_DIR}/test/${section}/*.c")
  FOREACH(case ${TEST_CASES})
    get_filename_component(case ${case} NAME_WE)
    add_test_case(${section} ${case})
  ENDFOREACH()
ENDFOREACH()