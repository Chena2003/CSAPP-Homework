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

int divide_power2(int x, int k) {
     int t = (x >> (sizeof(int) << 3 - 1)) & 0x1;

     return (x + (t << k) - t) >> k;
}

int main() {

     printf("%d\n", divide_power2(9, 2));
     printf("%d\n", divide_power2(-9, 2));
     printf("%d\n", divide_power2(20, 2));
     printf("%d\n", divide_power2(-20, 2));
     printf("%d\n", divide_power2(7, 2));

     return 0;
}