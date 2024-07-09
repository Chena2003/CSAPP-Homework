#include <stdio.h>

int main() {
    // unsigned u = 1;

    // printf("%x\n", u << (int)-1);

    // printf("%x\n", ~0 - 1);

    float f = 2.5;
    int t = (int)(f + 0.5);

    if(f - (int)f == 0.5) {
        t &= ~0 - 1;
        printf("%x\n", t);
    }

    return 0;
}