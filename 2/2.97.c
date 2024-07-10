#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <limits.h>

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

/* Get bit length for integer i. Return 32 when i is negative. */
int bits_length(int i) {
    if ((i & INT_MIN) != 0) {
        return 32;
    }

    int length = 0;
    unsigned u = (unsigned)i;
    while(u >= (1 << length)) {
        length++;
    }
    return length;
}

/* Generage mask for length len. e.g. 3->0x7 */
unsigned generate_mask(int len) {
    return (unsigned)-1 >> (32-len - 1) >> 1;
}

float_bits float_i2f(int i) {
    unsigned sign, exp, frac, exp_frac;
    unsigned bias = 0x7F;

    /* i = 0 */
    if (i == 0) {
        sign = 0;
        exp = 0;
        frac = 0;
        return sign << 31 | exp << 23 | frac;
    }

    /* i = INT_MIN */
    if (i == INT_MIN) {
        sign = 1;
        exp = 31 + bias;
        frac = 0;
        return sign << 31 | exp << 23 | frac;
    }

    sign = 0;
    /* i is negative */
    if (i < 0) {
        sign = 1;
        i = -i;
    }

    int length = bits_length(i);
    int flength = length - 1;
    unsigned mask = generate_mask(flength);
    unsigned f = i & mask;
    exp = bias + length - 1;

    // printf("%d %#x\n", length, mask);
    // printf("%#x %#x\n", f, exp);

    if (flength <= 23) {
        /* no overflow */
        frac = f << (23 - flength);
        exp_frac = exp << 23 | frac;

        // printf("%#x %#x\n", frac, exp_frac); 
    } else {
        /* overflow */
        int offset = flength - 23;
        frac = f >> offset;
        exp_frac = exp << 23 | frac;
        int round_mid = 1 << (offset - 1);
        int round_part = f & generate_mask(offset);

        /* round to even */
        if (round_part < round_mid) {

        } else if (round_part > round_mid) {
            exp_frac += 1;
        } else {
            if ((frac & 0x1) == 1) {
                exp_frac += 1;
            }
        }
    }
    return sign << 31 | exp_frac;
}


int main() {
    union databits t;    
    unsigned long long tt = (1ull << 32) - 1;
    for(unsigned i = 0; i < tt; i ++) {
        t.f = (float)(int)i;
        float_bits r = float_i2f(i);
        if(t.i != r) {
            show_byte((bytepointer)&i, sizeof i);
            show_byte((bytepointer)&t.i, sizeof i);
            show_byte((bytepointer)&r, sizeof r);
            // printf("%.10f %.10f\n", t.i, r);

            break;
        }
    }

    return 0;
}