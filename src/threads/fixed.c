#include "fixed.h"

int int_to_float(int n){
    return n * F;
}
int float_to_int(int x){
    return x / F;
} 
int float_to_int_round(int x){
    return (x >= 0)?(x + F / 2) / F:(x - F / 2) / F;
}
int float_add(int x, int y){
    return x + y;
}
int float_add_mix(int x, int n){
    return x + n * F;
}
int float_sub(int x, int y){
    return x - y;
}
int float_sub_mix(int x, int n){
    return x - n* F;
}
int float_mult(int x, int y){
    return ((int64_t)x) * y / F;
}
int float_mult_mix(int x, int n){
    return x * n;
}
int float_div(int x, int y){
    return ((int64_t)x) * F / y;
}
int float_div_mix(int x, int n){
    return x / n;
}