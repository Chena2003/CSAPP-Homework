#include <stdio.h>
#include <assert.h>

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

float_bits float_negate(float_bits f) {
    unsigned sign = f >> 31;
    unsigned exp = f >> 23 & 0xFF;
    unsigned frac = f & 0x7FFFFF;

    if(exp == 0xFF && frac != 0)
        return f;
    else
        return (!sign << 31) | (exp << 23) | frac; 
}

int main() {
    union databits t;    
    unsigned long long tt = (1ull << 32) - 1;
    for(unsigned i = 0; i < tt; i ++) {
        t.i = i;
        t.f = -t.f;
        unsigned r = float_negate(i);
        if(t.i != r) {
            show_byte((bytepointer)&t.i, sizeof i);
            show_byte((bytepointer)&i, sizeof i);
            show_byte((bytepointer)&r, sizeof r);
            printf("%u  %u\n", t.i, r);

            assert(0);
        }

        // assert(t.i == float_negate(i));
    }

    return 0;
}