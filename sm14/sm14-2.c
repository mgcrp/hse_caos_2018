#include <dlfcn.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    if (argc < 2) { return 0; }

    char * functionName = argv[1];
    void * handle = dlopen("/lib/libm.so.6", RTLD_LAZY);
    if (handle == NULL) { return 1; }
    void * function = dlsym(handle, functionName);
    if (function == NULL) { return 1; }

    double number_in;
    while ( (scanf("%lf", &number_in)) == 1 ) {
        // complicated stuff from seminar
        double result = ((double(*)(double)) function)(number_in);
        printf("%.10g\n", result);
    }

    return 0;
}
