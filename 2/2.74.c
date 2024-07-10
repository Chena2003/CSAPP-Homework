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

bool tsub_ok(int x, int y) {
     int r = x - y;

     int t1 = (x >> (sizeof(int) * 8 - 1)) & 0x1;
     int t2 = (y >> (sizeof(int) * 8 - 1)) & 0x1;
     int t3 = (r >> (sizeof(int) * 8 - 1)) & 0x1;

     return !((!t1 & t2 & t3) || (t1 & !t2 & !t3));
}

int main() {

     // printf(tsub_ok(0x80000000, 0x10000000)? "true\n": "false\n");
     // printf(tsub_ok(0x10000000, 0x1)? "true\n": "false\n");
     // printf(tsub_ok(0x10000000, 0x20000000)? "true\n": "false\n");
     // printf(tsub_ok(0x7fffffff, 0x80000000)? "true\n": "false\n");

     assert(!tsub_ok(INT_MIN, 1));
     assert(!tsub_ok(INT_MAX, -1));
     assert(tsub_ok(0, 0));
     assert(!tsub_ok(INT_MIN, INT_MAX));
     assert(!tsub_ok(INT_MAX, INT_MIN));
     assert(tsub_ok(10, 8));

     return 0;
}