#include <stdio.h>
#include <stdbool.h>

void show_bytes(unsigned char *p, unsigned int size) {
     printf("0x");
     for(unsigned int i = 0; i < size; i ++) {
          printf("%2x", p[i]);
     }
     puts("");
}

unsigned int func(unsigned int x, unsigned int y) {
     return (x & 0xff) | (y & (~0xff));
}

int main() {
     unsigned int x = 0x89abcdef;
     unsigned int y = 0x76543210;

     unsigned int t = func(x, y);

     printf("%d %d\n", sizeof x, sizeof y);

     show_bytes((unsigned char *)&x, sizeof(x));
     show_bytes((unsigned char *)&y, sizeof(y));
     show_bytes((unsigned char *)&t, sizeof(t));

     return 0;
}