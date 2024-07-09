#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>

union databits{
    float f;
    unsigned i;
};

typedef unsigned float_bits;

typedef unsigned char *bytepointer;

void show_byte(bytepointer p, unsigned int size) {
     printf("0x");
     for(unsigned int i = size - 1; i > 0; i --) { // 小端存储
          printf("%02x", p[i]);
     }
     printf("%02x", p[0]);
     puts("");
}

float_bits float_twice(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    // printf("%u %u %u\n", sign, exp, frac);

    if(exp == 0xFF)
        return f;

    unsigned flag = frac >> 22 & 0x1;
    if(!exp && !flag) {
        frac <<= 1;
    }
    else if(!exp && flag) {
        frac = (frac << 1) & 0x7FFFFF;
        exp ++;
    }
    else {
        exp ++;

        if(exp == 0xFF)
            frac = 0;
    }

    // printf("%u %u %u\n", sign, exp, frac);

    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    union databits t;    
    unsigned long long tt = (1ull << 32) - 1;
    for(unsigned i = 0; i < tt; i ++) {
        t.i = i;
        t.f = 2.0 * t.f;
        unsigned r = float_twice(i);
        if(t.i != r) {
            show_byte((bytepointer)&i, sizeof i);
            show_byte((bytepointer)&t.i, sizeof i);
            show_byte((bytepointer)&r, sizeof r);
            printf("%u  %u\n", t.i, r);

            // assert(0);
            break;
        }
    }

    return 0;
}