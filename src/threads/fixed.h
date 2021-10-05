#ifndef THREADS_FIXED_H
#define THREADS_FIXED_H

#include <stdint.h>

#define Q 14
#define P 17
#define F (1 << Q)


int int_to_float(int n);
int float_to_int(int x);
int float_to_int_round(int x);
int float_add(int x, int y);
int float_add_mix(int x, int n);
int float_sub(int x, int y);
int float_sub_mix(int x, int n);
int float_mult(int x, int y);
int float_mult_mix(int x, int n);
int float_div(int x, int y);
int float_div_mix(int x, int n);
//17.14 fixed-pointed number representation 에 맞게 구현하면 된다.

#endif