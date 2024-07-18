#include <stdio.h>
#include <assert.h>

#define Assert(cond, FMT, ...) \
    do { \
        if(!(cond)) { \
            fflush(stdout); \
            fprintf(stderr, FMT "\n", ##  __VA_ARGS__); \
            assert(cond); \
        } \
} while(0)


typedef union data{
    float f;
    unsigned i;
} databits;

// 条件传送指令
int find_range(float x) {
    int result;
    asm(
        "movl $3, %%edi;"
        "movl $2, %%esi;"
        "movl $1, %%edx;"
        "vxorps %%xmm1, %%xmm1, %%xmm1;"
        "movl $0, %0;"
        "vucomiss %%xmm1, %%xmm0;"
        "cmova %%esi, %0;"
        "cmove %%edx, %0;"
        "cmovp %%edi, %0;"
        : "=r"(result)
        : 
        : "%xmm1", "%edi", "%esi", "%edx"
    );

    return result;
}

int check_nan(unsigned u) {
    unsigned exp = u >> 23 & 0xFF;
    unsigned frac = u & 0x7FFFFF;

    if(exp == 0xFF && frac != 0) 
        return 1;
    
    return 0;
}

int main() {
    enum {NEG, ZERO, POS, NAN};

    databits t;
    unsigned U_MAX = ~0 - 1;
    for(unsigned i = 0; i < U_MAX; i ++) {
        t.i = i;

        int v = find_range(t.f);

        if(check_nan(t.i)) 
            Assert(v == NAN, "%#x", t.i);
        else if(t.f > 0) 
            Assert(v == POS, "%#x", t.i);
        else if(t.f == 0)
            Assert(v == ZERO, "%#x", t.i);
        else
            Assert(v == NEG, "%#x", t.i);
    }

    // t.i = 0x7f800001;
    // printf("%d\n", find_range(t.f));

    return 0;
}