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

int mul3div4(int x) {
     int r = x + (x << 1);

     int t = (r >> (sizeof(int) * 8 - 1)) & 0x3;

     return (r + t) >> 2;
}

int main() {

     printf("%d\n", mul3div4(1));
     printf("%d\n", mul3div4(2));
     printf("%d\n", mul3div4(-2));
     printf("%d\n", mul3div4(-6));

     return 0;
}