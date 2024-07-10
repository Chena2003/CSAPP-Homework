#include <stdio.h>
#include <assert.h>

int leftmost_one(unsigned x) {
    /* First, generate mask that all bits after the leftmost 1 are 1. */
    x |= x >> 16;
    x |= x >> 8;
    x |= x >> 4;
    x |= x >> 2;
    x |= x >> 1;
    /* Next, return the result. x && 1 deals with x = 0. 
     * (x>>1)+1 turns all the bits but leftmost to 0.
     */
    return (x >> 1) + ( x && 1);
}

int main() {
    assert(leftmost_one(0xff00)==0x8000);
    assert(leftmost_one(0x6600)==0x4000);
    return 0;
}