#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
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

/*
 * 3*x/4 should not overflow, then divide 4 first, and multiple 3
 * Rounding to zero:
 *		x is equal to m30(the most significant 30 bits) plus l2(the least significant 2 bits)
 *		x = m30 + l2
 *		m30 = x & ~0x3;
 *		l2 = x & 0x3;
 *		when x >= 0, m30d4m3 = (m30 >> 2) << 1 + (m30 >> 2), l2m3d4 = ((l2 << 1) + l2) >> 2;
 *		when x < 0, need bias, bias = 3
 */
int threefourths(int x) {
    int neg_flag = x & INT_MIN;
    int m30 = x & ~0x3;
    int l2 = x & 0x3;
    int m30d4m3 = ((m30 >> 2) << 1) + (m30 >> 2); // 计算前30位除四乘三
    int bias = 3; // 偏置值为4 - 1 = 3
    int l2m3 = (l2 << 1) + l2; // 先计算后两位乘三，减少误差
    (neg_flag) && (l2m3 = l2m3 + bias); // 处理负数情况
    int l2m3d4 = l2m3 >> 2; // 后两位除四
    return m30d4m3 + l2m3d4; // 前30位计算结果加上后两位计算结果
}

int main() {

     printf("%d\n", threefourths(1));
     printf("%d\n", threefourths(2));
     printf("%d\n", threefourths(-2));
     printf("%d\n", threefourths(-6));

     return 0;
}