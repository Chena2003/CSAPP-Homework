#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *bytepointer;

void show_byte(bytepointer p, unsigned int size) {
     printf("0x");
     for(unsigned int i = size - 1; i >= 0; i --) { // 小端存储
          printf("%02x", p[i]);
     }
     puts("");
}

unsigned srl(unsigned x, int k) {
     unsigned xsra = (int) x >> k;

     return xsra & ((1ull << (sizeof(int) * 8 - k)) - 1);
}

int sra(int x, int k) {
     unsigned xsrl = (unsigned) x >> k;

     int t = (x >> sizeof(int) * 8 - 1) & 0x1;

     return xsrl | ~(t << (sizeof(int) * 8 - k) - 1);
}

int main() {
     int x = 0xffffffff;
     for(int i = 0; i < sizeof(int) * 8; i ++) {
          assert((x >> i) == sra(x, i));
     }

     unsigned y = 0xffffffff;
     for(int i = 0; i < sizeof(int) * 8; i ++) {
          assert((y >> i) == srl(y, i));
     }

     return 0;
}