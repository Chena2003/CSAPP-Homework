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

    return i;
}

int float_f2i(float_bits f) {
    int sign = (f >> 31) ? -1 : 0;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if(exp < 127) {
        return 0;
    }
    else if(exp < 157) {
        unsigned lbits = lowbits(frac);
        unsigned dbits = 23 - lbits;
        unsigned mbits = exp - 126;

        printf("%u %u %u\n", lbits, dbits, mbits);

        frac = (frac | 0x800000) >> lbits << mbits;

        printf("%u\n", frac);

        unsigned flag = (frac >> dbits) & (frac >> (dbits - 1));

        return (frac >> dbits + flag) * sign;
    }
    else
        return 0x80000000;
}

int main() {
    union databits t;    
    unsigned long long tt = (1ull << 32) - 1;
    for(unsigned i = 0; i < tt; i ++) {
        t.i = i;
        unsigned m = (int)(t.f + 0.5);
        unsigned r = float_f2i(i);
        if(m != r) {
            show_byte((bytepointer)&i, sizeof i);
            show_byte((bytepointer)&m, sizeof i);
            show_byte((bytepointer)&r, sizeof r);
            printf("%f %u  %u\n",t.f, m, r);

            // assert(0);
            break;
        }
    }

    // union databits t;
    // t.i = 0x4f700000;
    // int m = (int)(t.f + 0.5);
    
    // show_byte((bytepointer)&m, sizeof(int));
    // printf("%f, %d\n", t.f, m);

    return 0;
}