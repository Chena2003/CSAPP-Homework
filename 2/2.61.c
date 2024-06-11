#include <stdio.h>
#include <stdbool.h>

typedef unsigned char *bytepointer;

void show_byte(bytepointer p, unsigned int size) {
     printf("0x");
     for(unsigned int i = 0; i < size; i ++) {
          printf("%2x", p[i]);
     }
     puts("");
}

bool func(int x) {
     return !(~x) || !x || !(~(x & 0xff)) || !((x >> (sizeof(x) - 1) * 8) & 0xff);    
}

int main() {
     printf("%d\n", func(0));
     printf("%d\n", func(0xffffffff));
     printf("%d\n", func(0xff000000));
     printf("%d\n", func(0xff));
     printf("%d\n", func(0x1));
     printf("%d\n", func(0xf));

     return 0;
}