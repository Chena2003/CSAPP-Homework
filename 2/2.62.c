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
     // int x = 0xffffffff;
     // int x = -1; // ~0
     int x = ~0;

     // return (x >> 8) == x;
     return !(x ^ (x >> 1));
}

int main() {

     printf(int_shifts_are_artithmetic()?"true\n":"false\n");

     return 0;
}