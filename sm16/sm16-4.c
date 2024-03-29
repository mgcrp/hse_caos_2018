#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// ОНА ПРОШЛА!!!

int main() {
    int number;
    pid_t root_pid = getpid();

    while (scanf("%d", &number) != EOF) {
        // Чтение прошло успешно - пораждаем форк
        pid_t pid = fork();
        // Проверка на ошибку при форке
        if (pid < 0) {
            if (getpid() == root_pid) {
                printf("-1\n");
                exit(0);
            }
            exit(1);
        }
        // Если находимся в родителе
        if (pid > 0) {
            // Ждем завершения порожденного процесса
            int waitpid_ret;
            waitpid(pid, &waitpid_ret, 0);
            if (!waitpid_ret) {
                // Если код 0 - т.е. все завершилось корректно
                // Печатаем цифру и выходим
                printf("%d\n", number);
                exit(0);
            } else {
                // Иначе - выходим с ошибкой
                // Последний завершаемый выводит -1
                if (getpid() == root_pid) {
                    printf("-1\n");
                    exit(0);
                }
                exit(1);
            }
            break;
        }
    }

    return 0;
}
