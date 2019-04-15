#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

enum { SIG_EXIT_CONST = 128, BIN_SH_FAILED = 127 };

int mysys(const char * str) {
    // Создание процесса
    int pid = fork();

    if (pid < 0) {
        // Ошибка создания процесса - return -1;
        return -1;
    } else if (pid == 0) {
        execl("/bin/sh", "sh", "-c", str, NULL);
        // Интерпретатор `/bin/sh` не может быть запущен -
        // функция завершается со значением 127
        _exit(BIN_SH_FAILED);
    }

    // Ожидание завершения процесса
    int waitpid_ret;
    waitpid(pid, &waitpid_ret, 0);

    if (WIFEXITED(waitpid_ret)) {
        // Завершение с кодом 0-127 - return <код>;
        return WEXITSTATUS(waitpid_ret);
    } else if (WIFSIGNALED(waitpid_ret)) {
        // Завершение из-за сигнала - return 128 + <сигнал>
        return SIG_EXIT_CONST + WTERMSIG(waitpid_ret);
    }

    return 0;
}
