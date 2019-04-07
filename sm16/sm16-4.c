#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

// TODO:
//  b = запоминаем пид главного процесса
//  while (считываение):
//      с = форк
//      if (с > 0):
//          d = waitpid
//          if (d == 0):
//              print(число)
//          else if (d == 1):
//          if (getpid() == b):
//              break;
//          плохой Exit
//

int main() {
    int number;
    pid_t root_pid = getpid();
    while (scanf("%d", &number) != EOF) {
        pid_t pid = fork();
        if (pid > 0) {
            int waitpid_ret;
            if (waitpid(pid, &waitpid_ret, WNOHANG)) {
                printf("%d\n", number);
                exit(0);
            } else {
                if (getpid() == root_pid) {
                    printf("-1\n");
                }
                exit(1);
            }
            break;
        }
    }
    return 0;
}
