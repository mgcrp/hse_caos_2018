#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int exec(const char * str) {
    // Функция запуска и проверки условия ¯\_(ツ)_/¯
    pid_t pid = fork();

    if (pid < 0) {
        // Ошибка запуска процесса - return 0;
        return 0;
    } else if (pid == 0) {
        // Всё ок - запускаем команду в процессе-ребенке
        execlp(str, str, NULL);
        exit(1);
    }
    int wait_ret;
    wait(&wait_ret);
    if (WIFEXITED(wait_ret)) {
        // Делаем логический вывод:
        //     [0 - в shell всё ок] -> True в С;
        //     [!0 - в shell не ок] -> False в С;
        return (WEXITSTATUS(wait_ret) == 0);
    }
}

int main(int argc, char * argv[]) {
    // Выполняем (<логический вывод 1> или <логический вывод 2>) и <логический вывод 3>
    // Так как вывод должен быть в shell-логике:
    //     !True - !0 as Bytes - 1 as C output;
    //     !False - !1 as Bytes - 0 as C output;
    return !( (exec(argv[1]) || exec(argv[2]) ) && exec(argv[3]) );
}
