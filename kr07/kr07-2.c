#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        // Открытие входного файла
        int file_in = open(argv[2], O_RDONLY);
        if (file_in < 0) { _exit(42); }
        dup2(file_in, STDIN_FILENO);

        // Открытие выходного файла
        int file_out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (file_out < 0) { _exit(42); }
        dup2(file_out, STDOUT_FILENO);

        // Открытие файла ошибок
        int file_err = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (file_err < 0) { _exit(42); }
        dup2(file_err, STDERR_FILENO);

        // Выполнение команды
        execlp(argv[1], argv[1], NULL);
        exit(0);
    }

    int wait_ret;
    wait(&wait_ret);
    printf("%d\n", wait_ret);
    return 0;
}
