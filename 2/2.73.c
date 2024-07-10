#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

typedef unsigned char *bytepointer;

void show_byte(bytepointer p, unsigned int size) {
     printf("0x");
     for(unsigned int i = size - 1; i > 0; i --) { // 小端存储
          printf("%02x", p[i]);
     }
     printf("%02x", p[0]);
     puts("");
}

int saturating_add(int x, int y) {
     int sum = x + y;

     int mask = INT_MIN;

     int posflag = !(x & mask) && !(y & mask) && (sum & mask); // 正溢出标志位
     int negflag = (x & mask) && (y & mask) && !(sum & mask); // 负溢出标志位

     (posflag && (sum = INT_MAX)) || (negflag && (sum = INT_MIN)); 

     return sum;
}

int main() {
    assert(saturating_add(0x80000000, 0x80000000)==INT_MIN);
    assert(saturating_add(0x10, 0x20)==0x30);
    assert(saturating_add(0x7FFFFFFF, 0x7FFFFFFF)==INT_MAX);

     return 0;
}