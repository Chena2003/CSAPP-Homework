#include <stdio.h>
#include <assert.h>

int int_size_is_32() {
    int set_msb = 1 << 31;

    /*
        不能直接将1左移32位，因为左移位数超出int位数时，为c语言未定义行为，由编译器决定，可能引发错误。
    */
    int beyond_msb = set_msb << 1; 

    return set_msb && !beyond_msb;
}

int int_size_is_32_16() {
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;

    return set_msb && !beyond_msb;
}

int main() {
    assert(int_size_is_32());
    assert(int_size_is_32_16());

    return 0;
}