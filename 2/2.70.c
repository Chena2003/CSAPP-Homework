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

bool fits_bits(int x, int n) {
     /*
     * 1 <= n <= w
     *
     * assume w = 8, n = 3
     * if x > 0
     *   0b00000010 is ok, 0b00001010 is not, and 0b00000110 is not yet (thanks itardc@163.com)
     * if x < 0
     *   0b11111100 is ok, 0b10111100 is not, and 0b11111000 is not yet
     *
     * the point is
     *   x << (w-n) >> (w-n) must be equal to x itself.
     *
     */
     int w = sizeof(int) << 3;
     int offset = w - n;
     return (x << offset >> offset) == x;
}
int main() {
     assert(!fits_bits(0xFF, 8));
     assert(!fits_bits(~0xFF, 8));

     assert(fits_bits(0b0010, 3));
     assert(!fits_bits(0b1010, 3));
     assert(!fits_bits(0b0110, 3));

     assert(fits_bits(~0b11, 3));
     assert(!fits_bits(~0b01000011, 3));
     assert(!fits_bits(~0b111, 3));

     return 0;
}