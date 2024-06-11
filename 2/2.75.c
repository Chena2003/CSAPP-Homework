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

unsigned unsigned_high_prod(unsigned x, unsigned y) {
     unsigned r = signed_high_prod(x, y);

     int x1 = (x >> (sizeof(unsigned) * 8 - 1)) & 0x1;
     int y1 = (y >> (sizeof(unsigned) * 8 - 1)) & 0x1;

     return r + x1 * (int)y + (int)x * y1 + x1 * y1 * (1ull << sizeof(unsigned) * 8);
}

int main() {

     return 0;
}