/* { dg-do run { target { riscv_vector } } } */
/* { dg-additional-options "--param=riscv-autovec-preference=scalable" } */

#include <assert.h>
#include "widen-7.c"

#define SZ 512

#define RUN(TYPE1, TYPE2, LIMIT)                                               \
  TYPE2 a##TYPE2[SZ];                                                          \
  TYPE1 b##TYPE1[SZ];                                                          \
  TYPE1 dst##TYPE1[SZ];                                                        \
  for (int i = 0; i < SZ; i++)                                                 \
    {                                                                          \
      a##TYPE2[i] = LIMIT + i % LIMIT;                                         \
      b##TYPE1[i] = LIMIT + i & LIMIT;                                         \
    }                                                                          \
  vwmul_##TYPE1_##TYPE2 (dst##TYPE1, a##TYPE2, b##TYPE1, SZ);                  \
  for (int i = 0; i < SZ; i++)                                                 \
    assert (dst##TYPE1[i] == (((TYPE1) a##TYPE2[i]) * b##TYPE1[i]));

#define RUN_ALL()                                                              \
  RUN (int16_t, int8_t, -128)                                                  \
  RUN (uint16_t, uint8_t, 255)                                                 \
  RUN (int32_t, int16_t, -32768)                                               \
  RUN (uint32_t, uint16_t, 65535)                                              \
  RUN (int64_t, int32_t, -2147483648)                                          \
  RUN (uint64_t, uint32_t, 4294967295)

int
main ()
{
  RUN_ALL ()
}
