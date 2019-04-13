#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char * argv[]) {
    if (argc < 4) {
        return 0;
    }

    double number;
    sscanf(argv[1], "%f", &number);
    char prevFile[] = "";

    int current_arg = 2;
    while (current_arg <= argc - 1) {
        char * functionName = argv[current_arg + 1];
        void * handle;
        if (argv[current_arg] == "-") {
            void * handle = dlopen(prevFile, RTLD_LAZY);
        } else {
            void * handle = dlopen(argv[current_arg], RTLD_LAZY);
        }
        if (handle == NULL) { continue; }
        prevFile = argv[current_arg];
        void * function = dlsym(handle, functionName);
        if (function == NULL) { continue; }
        number = ((double(*)(double)) function)(number);
    }

    printf("%.6g\n", number);
    return 0;
}
