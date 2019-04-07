#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; ++i) {
        // Выводим то, что от нас просят
        if (i == N - 1) {
            printf("%d\n" , i + 1);
        } else {
            printf("%d ", i + 1);
        }

        // Все остальное уходит в буффер
        fflush(stdout);

        // Если напечатано последнее число - выход
        if (i == N - 1) {
            exit(0);
        }
        // Иначе - генерим новый процесс
        pid_t pid = fork();
        // Если возникла ошибка - выходим с кодом 1
        if (pid < 0) {
            exit(1);
        }
        // Прерываем цикл для процесса-родителя
        if (pid != 0) {
            break;
        }
    }

    wait(NULL);
    return 0;
}
