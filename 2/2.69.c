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

unsigned rotate_left(unsigned x, int n) {
     /*
          在下面做法中，当n为0时，x右移32位，引发未定义行为，产生值仍为x本身，符合预期。
          更好的做法是
          unsigned t1 = x >> (sizeof(int) * 8 - n - 1) >> 1;
     */
     unsigned t1 = x >> (sizeof(int) * 8 - n);
     unsigned t2 = x << n;

     return t1 | t2;
}

int main() {
     unsigned x = 0x12345678;
     for(int i = 0; i <= 32; i += 4) {
          unsigned t = rotate_left(x, i);

          show_byte((bytepointer)&t, sizeof t);
     }

     return 0;
}