#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned char *bytepointer;

void show_byte(bytepointer p, unsigned int size) {
     printf("0x");
     for(unsigned int i = size - 1; i > 0; i --) { // 小端存储
          printf("%02x", p[i]);
     }
     printf("%02x", p[0]);
     puts("");
}

int gen_bits1(int k) {
     return ~((1ull << k) - 1);
}

int gen_bits2(int k, int j) {
     return ((1ull << k + j) - 1) - ((1ull << j) - 1);
}

int main() {
     for(int i = 0; i <= 32; i ++) {
          int t = gen_bits2(i, 4);

          show_byte((bytepointer)&t, sizeof t);
     }


     return 0;
}