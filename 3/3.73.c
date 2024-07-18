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

void show_byte(char *p, unsigned size) {
     printf("0x");
     for(unsigned int i = size - 1; i > 0; i --) { // 小端存储
          printf("%02x", p[i]);
     }
     printf("%02x", p[0]);
     puts("");
}

int find_range(float x) {
    int result;
    asm(
        "vxorps %%xmm1, %%xmm1, %%xmm1;"
        "vucomiss %%xmm1, %%xmm0;"
        "ja .T1;"
        "jp .T2;"
        "jb .T3;"
        "movl $1, %0;"
        "jmp .T0;"
        ".T1:\t movl $2, %0;"
        "jmp .T0;"
        ".T2:\t movl $3, %0;"
        "jmp .T0;"
        ".T3:\t movl $0, %0;"
        ".T0:\t "      
        : "=r"(result)
        : 
        : "%xmm1"
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