#include <dlfcv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MAX_ARGS_BYTES = 64
};

typedef struct Value {
    union {
        int i;
        double d;
        char * s;
    };
    char ty;
} Value;

typedef struct Stack {
    unsigned char raw[MAX_ARGS_BYTES];
} Stack;

typedef struct Call {
    void * (*fp)(Stack);
    int argc;
    Value * argv;
    char ret;
} Call;

void value_print(const Value v) {
    switch (v.ty) {
        case 'v':
            break;
        case 'i':
            printf("%d\n", v.i);
            break;
        case 'd':
            printf("%.10g\n", v.d);
            break;
        case 's':
            printf("%s\n", v.s);
            break;
        default:
            break;
    }
}

size_t value_size (const Value v) {
    
}
