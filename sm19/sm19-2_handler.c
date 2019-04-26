#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    int pid = strtol(argv[1], NULL, 10);
    int mode = strtol(argv[2], NULL, 10);

    if (mode == 1) {
        kill(pid, SIGUSR1);
    } else if (mode == 2) {
        kill(pid, SIGUSR2);
    }

    return 0;
}
