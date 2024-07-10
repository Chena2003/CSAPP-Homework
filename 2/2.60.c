#include <stdio.h>

typedef unsigned char *bytepointer;

void show_byte(bytepointer p, unsigned int size) {
     printf("0x");
     for(unsigned int i = 0; i < size; i ++) {
          printf("%2x", p[i]);
     }
     puts("");
}

// 通过读写字节序列
// unsigned replace_byte(unsigned x , int i, unsigned char b) {
//      unsigned char* p = (unsigned char *)&x;

//      *(p + i) = b;

//      return *(unsigned *)p;
// }

// 通过移位操作
unsigned replace_byte(unsigned x , int i, unsigned char b) {
     unsigned mask = ((unsigned)0xFF) << (i << 3);
     unsigned des_bytes = ((unsigned)b) << (i << 3);

     return (x & ~mask) | des_bytes;
}

int main() {
     unsigned x = replace_byte(0x12345678, 2, 0xAB);
     show_byte((bytepointer) &x, sizeof x);

     x = replace_byte(0x12345678, 0, 0xAB);
     show_byte((bytepointer) &x, sizeof x);

     return 0;
}