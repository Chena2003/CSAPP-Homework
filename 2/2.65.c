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

// 分治法统计x中1的个数 ∣x∣
int odd_ones(unsigned x) {
     x = (x & 0x55555555) + ((x >> 1) & 0x55555555);
     x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
     x = (x & 0x0F0F0F0F) + ((x >> 4) & 0x0F0F0F0F);
     x = (x & 0x00FF00FF) + ((x >> 8) & 0x00FF00FF);
     x = (x & 0x0000FFFF) + ((x >> 16) & 0x0000FFFF);
     return x & 0x1;
}

 int main() {
     unsigned uval = 0x10101010;
     assert(!odd_ones(uval));
     uval = 0x10101011;
     assert(odd_ones(uval));

     return 0;
}