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

int xbyte(unsigned word, int bytenum) {
     return ((int)word << (3 - bytenum) * 8) >> 24;
}

int main() {
     unsigned t = 0x87654321;

     for(int i = 0; i < 4; i ++) {
          unsigned x = xbyte(t, i);
          show_byte((bytepointer)&x, sizeof x);
     }

     return 0;
}