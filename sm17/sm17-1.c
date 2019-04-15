#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {
    pid_t pid = fork();

    if (pid == 0) {
        // Открытие входного файла
        int file_in = open(argv[2], O_RDONLY);
        dup2(file_in, STDIN_FILENO);

        // Открытие выходного файла
        int file_out = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
        dup2(file_out, STDOUT_FILENO);

        // Выполнение команды
        execlp(argv[1], argv[1], NULL);
        exit(1);
    }

    wait(NULL);
    return 0;
}
