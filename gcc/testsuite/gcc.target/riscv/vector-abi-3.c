/* { dg-do compile } */
/* { dg-options "-march=rv64gcv -mabi=lp64d" } */

#include "riscv_vector.h"

vint32m1_t*
fun (vint32m1_t* a) {  return a; }  /* { dg-bogus "the scalable vector type" } */

void
bar ()
{
  vint32m1_t a;
  fun (&a);
}
