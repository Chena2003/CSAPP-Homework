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

unsigned lowbits(unsigned x) {
    unsigned t = x & -x;

    int i;
    for(i = 0; i < 32; i ++) {
        if(t >> i & 0x1)
        break;
    }

    return t ? i : 23;
}

int float_f2i(float_bits f) {
    int sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;
    unsigned bias = 0x7F;

    if(exp < bias) {
        return 0;
    }
    else if(exp >= 31 + bias) {
        return 0x80000000;
    }
    else {
        unsigned res;
        unsigned E = exp - bias;
        unsigned M = frac | 0x800000;

        if(E > 23)
            res = M << (E - 23);
        else
            res = M >> (23 - E);

        return sign ? -res : res;
    }
}

int main() {
    union databits t;    
    unsigned long long tt = (1ull << 32) - 1;
    for(unsigned i = 0; i < tt; i ++) {
        t.i = i;
        int m = (int)t.f;

        int r = float_f2i(i);
        if(m != r) {
            show_byte((bytepointer)&i, sizeof i);
            show_byte((bytepointer)&m, sizeof i);
            show_byte((bytepointer)&r, sizeof r);
            printf("%.10f %d %d\n", t.f, m, r);

            break;
        }
    }

    return 0;
}