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

// lowbit
bool odd_ones(unsigned x) {
     
}

 int main() {



     return 0;
}