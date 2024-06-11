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

bool int_shifts_are_artithmetic() {
     int x = 0xffffffff;

     return (x >> 8) == x;
}

int main() {

     printf(int_shifts_are_artithmetic()?"true\n":"false\n");

     return 0;
}