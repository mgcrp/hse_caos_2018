#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char * argv[]) {
    // argv[0] - имя файла
    // argv[1] - float x0
    // argv[2] - первая библиотека -> (2 * i) - i-ая библиотека
    // argc[3] - первая функция -> (2 * i + 1) - i-ая функция
    if (argc == 2) {
        double number;
        sscanf(argv[1], "%f", &number);
        printf("%.6g\n", number);
        return 0;
    } else if (argc < 4) {
        return 0;
    }

    // Считываю первый float
    double number;
    sscanf(argv[1], "%f", &number);
    // Индекс предыдущей библиотеки
    int prev_lib = 2;
    // Индекс текущей библиотеки
    int current_arg = 2;

    while (current_arg <= argc - 1) {
        char * functionName = argv[current_arg + 1];
        void * handle;

        if (strcmp(argv[current_arg], "-")) {
            // Не равно "-"
            void * handle = dlopen(argv[current_arg], RTLD_LAZY);
            prev_lib = current_arg;
        } else {
            // равно "-"
            void * handle = dlopen(argv[prev_lib], RTLD_LAZY);
        }

        if (handle == NULL) { continue; }
        void * function = dlsym(handle, functionName);
        if (function == NULL) { continue; }
        number = ((double(*)(double)) function)(number);
        if (dlclose(handle) < 0) { exit(1); }

        current_arg += 2;
    }

    printf("%.6g\n", number);
    return 0;
}
