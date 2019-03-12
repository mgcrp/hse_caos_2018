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
