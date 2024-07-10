#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *bytepointer;

void show_byte(bytepointer p, unsigned int size) {
     printf("0x");
     for(unsigned int i = size - 1; i > 0; i --) { // 小端存储
          printf("%02x", p[i]);
     }
     printf("%02x", p[0]);
     puts("");
}

int signed_high_prod(int x, int y) {
     long long t = (long long)x * y;

     return t >> 32;
}

unsigned unsigned_high_prod(unsigned x, unsigned y) {
     unsigned r = signed_high_prod(x, y);

     int x1 = (x >> (sizeof(unsigned) * 8 - 1)) & 0x1;
     int y1 = (y >> (sizeof(unsigned) * 8 - 1)) & 0x1;

     return r + x1 * y + x * y1;
}

unsigned unsigned_high_prod_for_test(unsigned x, unsigned y) {
    unsigned long long prod = (unsigned long long)x * y;
    return prod >> 32;
}

int main() {
    unsigned x = 0x12345678;
    unsigned y = 0xFFFFFFFF;
    assert(unsigned_high_prod(x, y) == unsigned_high_prod_for_test(x, y));
    return 0;
}