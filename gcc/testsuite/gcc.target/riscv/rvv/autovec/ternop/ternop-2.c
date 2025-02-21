/* { dg-do compile } */
/* { dg-additional-options "-march=rv32gcv -mabi=ilp32d --param=riscv-autovec-preference=scalable -fno-schedule-insns" } */

#include <stdint-gcc.h>

#define TEST_TYPE(TYPE)                                                        \
  __attribute__ ((noipa)) void ternop_##TYPE (TYPE *__restrict dest1,          \
					      TYPE *__restrict dest2,          \
					      TYPE *__restrict dest3,          \
					      TYPE *__restrict src1,           \
					      TYPE *__restrict src2, int n)    \
  {                                                                            \
    for (int i = 0; i < n; ++i)                                                \
      {                                                                        \
	dest1[i] += src1[i] * src2[i];                                         \
	dest2[i] += src1[i] * dest1[i];                                        \
	dest3[i] += src2[i] * dest2[i];                                        \
      }                                                                        \
  }

#define TEST_ALL()                                                             \
  TEST_TYPE (int8_t)                                                           \
  TEST_TYPE (uint8_t)                                                          \
  TEST_TYPE (int16_t)                                                          \
  TEST_TYPE (uint16_t)                                                         \
  TEST_TYPE (int32_t)                                                          \
  TEST_TYPE (uint32_t)                                                         \
  TEST_TYPE (int64_t)                                                          \
  TEST_TYPE (uint64_t)

TEST_ALL ()

/* { dg-final { scan-assembler-times {\tvmacc\.vv} 8 } } */
/* { dg-final { scan-assembler-not {\tvmv} } } */
