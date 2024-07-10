#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

typedef unsigned char *bytepointer;

void show_byte(bytepointer p, unsigned int size) {
     printf("0x");
     for(unsigned int i = size - 1; i > 0; i --) { // 小端存储
          printf("%02x", p[i]);
     }
     printf("%02x", p[0]);
     puts("");
}

// int lower_one_mask(int n) {
//      return (1ull << n) - 1; // 使用long long类型处理n为32的情况
// }

// 更好的解决方法
int lower_one_mask(int n) {
     return (unsigned)-1 >> (32 - n); 
}

int main() {
     for(int i = 1; i <= 32; i ++) {
          int t = lower_one_mask(i);

          show_byte((bytepointer)&t, sizeof t);
     }

     return 0;
}