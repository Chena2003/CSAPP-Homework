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

void *calloc(size_t nmemb, size_t size) {
     if(!nmemb || !size)
          return NULL;

     size_t r = nmemb * size;

     if(r / nmemb != size) // 判断乘法是否溢出
          return NULL;

     void *p = malloc(r);
     if(!p)
          return NULL;

     memset(p, 0, r);

     return p;
}

int main() {
     if(calloc(0x80000000, 4) == NULL)
          puts("Ture");
     else
          puts("False");

     return 0;
}