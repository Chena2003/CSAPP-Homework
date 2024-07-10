#include <stdio.h>
#include <stdint.h>
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

int gen_bits1(int k) {
     return ~((1ull << k) - 1);
}

// int gen_bits1(int k) {
     // return -1  << k;
// }

// int gen_bits2(int k, int j) {
//      return ((1ull << k + j) - 1) - ((1ull << j) - 1);
// }

int gen_bits2(int k, int j) {
     return (unsigned)-1 << (32 - k - 1) << 1 >> (32 - k - j);
}

// int gen_bits2(int k, int j) {
//      return ~(-1 << k) << j;
// }

int main() {
     // for(int i = 0; i <= 32; i ++) {
     //      int t = gen_bits2(i, 4);

     //      show_byte((bytepointer)&t, sizeof t);
     // }


    assert(gen_bits1(3) == 0xFFFFFFF8);
    assert(gen_bits2(3, 4) == 0x00000070);

     return 0;
}