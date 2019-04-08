#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum {
    SIG_EXIT_CONST = 128,
    CANNOT_EXEC_SHELL = 127
};

int mysys(const char * str) {
    int pid = fork();
    if (pid < 0) {
        return -1;
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        _exit(CANNOT_EXEC_SHELL);
    }

    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    } else if (WIFSIGNALED(status)) {
        return SIG_EXIT_CONST + WTERMSIG(status);
    }
    return 0;
}
