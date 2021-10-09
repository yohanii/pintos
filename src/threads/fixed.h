#ifndef THREADS_FIXED_H
#define THREADS_FIXED_H

#include <stdint.h>

#define Q 14
#define P 17
#define F (1 << Q)


int int_to_fixed(int n){
    return n * F;
}
int fixed_to_int(int x){
    return x / F;
} 
int fixed_to_int_round(int x){
    return (x >= 0)?(x + F / 2) / F:(x - F / 2) / F;
}
int fixed_add(int x, int y){
    return x + y;
}
int fixed_add_mix(int x, int n){
    return x + n * F;
}
int fixed_sub(int x, int y){
    return x - y;
}
int fixed_sub_mix(int x, int n){
    return x - n* F;
}
int fixed_mult(int x, int y){
    return ((int64_t)x) * y / F;
}
int fixed_mult_mix(int x, int n){
    return x * n;
}
int fixed_div(int x, int y){
    return ((int64_t)x) * F / y;
}
int fixed_div_mix(int x, int n){
    return x / n;
}

#endif