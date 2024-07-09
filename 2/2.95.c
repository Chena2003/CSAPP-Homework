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

float_bits float_half(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    // printf("%u %u %u\n", sign, exp, frac);

    if(exp == 0xFF)
        return f;

    unsigned flag = (frac & 0x1) & (frac >> 1 & 0x1);
    if(!exp) {
        frac = (frac >> 1) + flag;
    }
    else if(exp == 1) {
        frac = ((frac | 0x800000) >> 1) + flag;
        exp --;
    }
    else {
        exp --;
    }

    return (sign << 31) | (exp << 23) | frac;
}

int main() {
    union databits t;    
    unsigned long long tt = (1ull << 32) - 1;
    for(unsigned i = 0; i < tt; i ++) {
        t.i = i;
        t.f = 0.5 * t.f;
        unsigned r = float_half(i);
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