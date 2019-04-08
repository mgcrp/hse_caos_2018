#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int exec_logical(char * cmd) {
    pid_t pid = fork();
    if (pid < 0) {
        return 0;
    } else if (pid == 0) {
        execlp(cmd, cmd, NULL);
        exit(1);
    }

    int status;
    wait(&status);
    if (WIFEXITED(status)) {
        return (WEXITSTATUS(status) == 0);
    }
}

int main(int argc, char ** argv) {
    return !( (exec_logical(argv[1]) || exec_logical(argv[2]) ) && exec_logical(argv[3]) );
}
