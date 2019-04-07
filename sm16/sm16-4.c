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
        pid_t fork_ret = fork();
        if (fork_ret > 0) {
            int waitpid_ret;
            waitpid(fork_ret, &waitpid_ret, WNOHANG);
            if (waitpid_ret == 0) {
                printf("%d\n", number);
                exit(0);
            } else if (getpid() == root_pid) {
                break;
            } else {
                exit(1);
            }
        }
    }
    return 0;
}
