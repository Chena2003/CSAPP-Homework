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
    int sign = (f >> 31) ? -1 : 1;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    // printf("%u %u\n", exp, frac);

    if(exp < 126) {
        return 0;
    }
    else if(exp < 127) {
        return frac ? 1 : 0;
    }
    else if(exp < 157) {
        unsigned lbits = lowbits(frac);
        unsigned dbits = 23 - lbits;
        int mbits = exp - 127;

        printf("%u %u %d\n", lbits, dbits, mbits);

        printf("%x\n", frac);

        frac = (frac | 0x800000) >> lbits << mbits;

        printf("%x\n", frac);

        unsigned flag = dbits ? (frac >> dbits & 0x1) & (frac >> (dbits - 1) & 0x1) : 0;

        printf("%u\n", flag);

        return ((frac >> dbits) + flag) * sign;
    }
    else
        return 0x80000000;
}

int main() {
    // union databits t;    
    // unsigned long long tt = (1ull << 32) - 1;
    // for(unsigned i = 0; i < tt; i ++) {
    //     t.i = i;
    //     int m = (int)(t.f + 0.5);

    //     if(fabs(t.f - (int)t.f - 0.5) < 1e-9) {
    //         m &= ~0 - 1;
    //     }

    //     int r = float_f2i(i);
    //     if(m != r) {
    //         show_byte((bytepointer)&i, sizeof i);
    //         show_byte((bytepointer)&m, sizeof i);
    //         show_byte((bytepointer)&r, sizeof r);
    //         printf("%.10f %d %d\n", t.f, m, r);

    //         break;
    //     }
    // }

    union databits t;
    t.i = 0x40200001;
    // int m = (int)(t.f + 0.5);
    int r = float_f2i(t.i);
    
    // show_byte((bytepointer)&m, sizeof(int));
    // printf("%f, %d\n", t.f, m);
    printf("%d %d\n", r, (int)t.f);

    return 0;
}