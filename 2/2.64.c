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

bool any_odd_one(unsigned x) {
     // return x & 0xaaaa;
     return !!(x & 0xAAAA);
}

int main() {
     puts(any_odd_one(0)?"1":"0");
     puts(any_odd_one(1)?"1":"0");
     puts(any_odd_one(2)?"1":"0");
     puts(any_odd_one(3)?"1":"0");
     puts(any_odd_one(4)?"1":"0");
     puts(any_odd_one(10)?"1":"0");


     return 0;
}