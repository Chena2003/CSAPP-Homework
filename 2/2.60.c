#include <stdio.h>

typedef unsigned char *bytepointer;

void show_byte(bytepointer p, unsigned int size) {
     printf("0x");
     for(unsigned int i = 0; i < size; i ++) {
          printf("%2x", p[i]);
     }
     puts("");
}

unsigned replace_byte(unsigned x , int i, unsigned char b) {
     unsigned char* p = (unsigned char *)&x;

     *(p + i) = b;

     return *(unsigned *)p;
}

int main() {
     unsigned x = replace_byte(0x12345678, 2, 0xAB);
     show_byte((bytepointer) &x, sizeof x);

     x = replace_byte(0x12345678, 0, 0xAB);
     show_byte((bytepointer) &x, sizeof x);

     return 0;
}